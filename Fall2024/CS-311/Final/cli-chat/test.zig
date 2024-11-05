const std = @import("std");
const net = std.net;
const ClientMap = std.array_hash_map.AutoArrayHashMap(net.Address, i32);
const print = std.debug.print;

pub fn main() !void {
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();
    const allocator = gpa.allocator();

    const argv = try std.process.argsAlloc(allocator);
    defer std.process.argsFree(allocator, argv);

    if (argv.len == 1) {
        print("no args given.\n", .{});
        return;
    }

    const clientMap: ClientMap = ClientMap.init(allocator);
    _ = clientMap;

    var isAdmin: bool = undefined;
    const host = "127.0.0.1";
    const testStream: net.Stream = switch (argv[1][0]) {
        'h' => stream: {
            try hostServer(host);

            isAdmin = true;
            break :stream undefined;
        },
        'j' => stream: {
            if (argv.len <= 2) {
                print("Bad argument.\n", .{});
                return;
            }

            isAdmin = false;
            const port: u16 = try std.fmt.parseUnsigned(u16, argv[2], 0);
            try joinServer(allocator, host, port);

            break :stream undefined;
        },
        else => {
            print("Bad argument.\n", .{});
            return;
        },
    };
    //defer testStream.close();
    _ = testStream;
}

pub fn hostServer(ipStr: []const u8) !void {
    const ipv4Addr = try net.Ip4Address.parse(ipStr, 0);
    const addr = net.Address{ .in = ipv4Addr };
    var server = try addr.listen(.{
        .reuse_address = true,
    });
    defer server.deinit();

    print("listening on port: {}\n", .{server.listen_address.getPort()});

    const client = try server.accept();
    defer client.stream.close();

    var buf: [1024:0]u8 = undefined;

    _ = try client.stream.reader().read(&buf);
    print("got: {s}", .{buf});

    std.mem.copyForwards(u8, &buf, "ni nao.\n");

    _ = try client.stream.writer().write(&buf);
}

pub fn joinServer(allocator: std.mem.Allocator, name: []const u8, port: u16) !void {
    const stream = try net.tcpConnectToHost(allocator, name, port);
    defer stream.close();

    var buf: [1024:0]u8 = undefined;
    std.mem.copyForwards(u8, &buf, "no no.\n");

    _ = try stream.writer().write(&buf);

    _ = try stream.reader().read(&buf);
    print("got: {s}", .{buf});
}
