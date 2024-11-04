const std = @import("std");
const ArrayList = std.ArrayList;
const net = std.net;
const print = std.debug.print;

pub fn main() !void {
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();
    const allocator = gpa.allocator();

    const host: []const u8 = "127.0.0.1";
    var server = try connect(host);
    defer server.deinit();
    print("Listening on {}, access this port to end the program\n", .{server.listen_address.getPort()});

    // client communication
    // WIP: proper error handling
    // var client: net.Server.Connection = undefined;

    // if (server.accept()) |connection| {
    //     client = connection;
    //     defer client.stream.close();
    // } else |err| {
    //     print("oopsie, {}", .{err});
    //     return;
    // }

    var client = try server.accept();
    defer client.stream.close();

    print("Connection received! {} is sending data.\n", .{client.address});

    var messages = ArrayList([]u8).init(allocator);
    defer {
        while (messages.popOrNull()) |message| {
            allocator.free(message);
        }
        messages.deinit();
    }

    while (true) {
        if (client.stream.reader().readUntilDelimiterAlloc(allocator, 0, 1024)) |str| {
            if (str.len != 0) {
                try messages.append(str);
                print("{}: {s}\n", .{ client.address, messages.getLast() });
            }
        } else |err| switch (err) {
            error.EndOfStream => {
                print("\n{}::{} left the room.", .{ client.address, client.stream.handle });
                break;
            },
            else => {
                print("oops, {}", .{err});
                break;
            },
        }
    }
    print("\nQuitting...\n", .{});
}

pub fn connect(ipStr: []const u8) !net.Server {
    const ipv4Addr = try net.Ip4Address.parse(ipStr, 0);
    const addr = net.Address{ .in = ipv4Addr };
    const server = try addr.listen(.{
        .reuse_address = true,
    });

    return server;
}
