const std = @import("std");
const ArrayList = std.ArrayList;
const net = std.net;
const Thread = std.Thread;
const array_hash_map = std.array_hash_map;
const print = std.debug.print;
const expectType = std.atomic.Value(u32); // type used in Thread.Futex.wait's expect param

const ClientData = struct {
    name: []const u8,
    stream: *const net.Stream,
};
const ClientMap = array_hash_map.AutoArrayHashMap(net.Address, ClientData);

const ClientStateInfo = struct { clients: *ClientMap, nClients: *const expectType, MAX_CLIENTS: u32, MAP_ACCESS: *Thread.Mutex };

pub fn main() !void {
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();
    const allocator = gpa.allocator();

    const MAX_THREADS: usize = try Thread.getCpuCount();
    const MAX_CLIENTS: usize = MAX_THREADS / 4;

    // client communication
    var clients: ClientMap = ClientMap.init(allocator);
    defer clients.deinit();

    const clientCountAtomic: expectType = expectType.init(0);
    var MAP_ACCESS: Thread.Mutex = Thread.Mutex{};
    const clientStateInfo: ClientStateInfo = .{ .clients = &clients, .nClients = &clientCountAtomic, .MAX_CLIENTS = @as(u32, @truncate(MAX_CLIENTS)), .MAP_ACCESS = &MAP_ACCESS };

    const host: []const u8 = "127.0.0.1";
    var server = try initServer(host);
    defer server.deinit();
    print("Listening on port {}\n", .{server.listen_address.getPort()});

    const joinThread = try Thread.spawn(.{}, handleJoinRequest, .{ &server, &clientStateInfo });
    defer joinThread.detach();

    // WIP: proper error handling
    // var client: net.Server.Connection = undefined;

    // if (server.accept()) |connection| {
    //     client = connection;
    //     defer client.stream.close();
    // } else |err| {
    //     print("oopsie, {}", .{err});
    //     return;
    // }

    // var client = try server.accept();
    // defer client.stream.close();

    // print("Connection received! {} is sending data.\n", .{client.address});

    // var messages = ArrayList([]u8).init(allocator);
    // defer {
    //     while (messages.popOrNull()) |message| {
    //         allocator.free(message);
    //     }
    //     messages.deinit();
    // }

    // while (true) {
    //     if (client.stream.reader().readUntilDelimiterAlloc(allocator, 0, 1024)) |str| {
    //         if (str.len != 0) {
    //             try messages.append(str);
    //             print("{}: {s}\n", .{ client.address, messages.getLast() });
    //         }
    //     } else |err| switch (err) {
    //         error.EndOfStream => {
    //             print("\n{}::{} left the room.", .{ client.address, client.stream.handle });
    //             break;
    //         },
    //         else => {
    //             print("oops, {}", .{err});
    //             break;
    //         },
    //     }
    // }
    print("\nQuitting...\n", .{});
}

pub fn initServer(ipStr: []const u8) !net.Server {
    const ipv4Addr = try net.Ip4Address.parse(ipStr, 0);
    const addr = net.Address{ .in = ipv4Addr };
    const server = try addr.listen(.{
        .reuse_address = true,
    });

    return server;
}

pub fn handleJoinRequest(hostServer: *net.Server, clientStateInfo: *const ClientStateInfo) !void {
    while (true) {
        Thread.Futex.wait(clientStateInfo.*.nClients, clientStateInfo.*.MAX_CLIENTS);

        // connection should close when map removes client
        const client = try hostServer.accept();

        clientStateInfo.*.MAP_ACCESS.*.lock();

        const entry = try clientStateInfo.*.clients.*.getOrPut(client.address);
        if (entry.found_existing) {
            clientStateInfo.*.MAP_ACCESS.*.unlock();
            return error.DupeClient;
        } else {
            entry.value_ptr.* = .{ .name = undefined, .stream = &client.stream };
            clientStateInfo.*.nClients.*.;
        }

        print("{} joined the chat.\n", .{client.address});

        clientStateInfo.*.MAP_ACCESS.*.unlock();
    }
}
