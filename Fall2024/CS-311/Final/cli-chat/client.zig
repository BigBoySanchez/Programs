const std = @import("std");
const net = std.net;
const print = std.debug.print;

pub fn main() !void {
    print("Connecting...", .{});

    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();
    const allocator = gpa.allocator();

    const argv = try std.process.argsAlloc(allocator);
    defer std.process.argsFree(allocator, argv);

    if (argv.len == 1) {
        print("no args given.\n", .{});
        return;
    }

    const name: []const u8 = "localhost";
    const port: u16 = try std.fmt.parseUnsigned(u16, argv[1], 0);

    var stream = try net.tcpConnectToHost(allocator, name, port);
    defer stream.close();

    print("\rConnected.                                           \n", .{});

    var stdIn = std.io.getStdIn();

    var buf: [1024:0]u8 = undefined;
    const quitStr = "-q";

    while (true) {
        var inputLen: usize = 0;
        while (inputLen < buf.len) {
            buf[inputLen] = try stdIn.reader().readByte();
            if (buf[inputLen] == '\n') break;
            inputLen += 1;
        }

        if (buf[inputLen - 1] == '\r') inputLen -= 1;
        buf[inputLen] = 0;

        if (inputLen == quitStr.len and std.mem.eql(u8, buf[0..quitStr.len], quitStr)) break;

        try stream.writer().writeAll(buf[0 .. inputLen + 1]);
    }

    // can do more things after leaving room
}
