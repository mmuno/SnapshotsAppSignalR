// ReSharper disable UnusedMember.Global

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Threading;
using System.Threading.Tasks;
using Microsoft.AspNetCore.SignalR;

namespace SnapshotsAppSignalR.Server.Hubs
{
    public class SnapshotsHub : Hub
    {
        public async Task SendSnapshot(int snapshotId, int ssCount)
        {
            Debug.WriteLine($"Sending Snapshot {ssCount}");
            var randNum = new Random();
            var random = Enumerable.Repeat(0, 700).Select(ii => randNum.Next(-1000, 1000));
            await Clients.All.SendAsync("ReceiveMessage", random.ToArray());
            await Task.Delay(50);
        }

        public async IAsyncEnumerable<int[]> SnapshotsStream(
            [EnumeratorCancellation]
            CancellationToken cancellationToken)
        {
            var randNum = new Random();
            var ssCount = 0;
            while (true)
            {
                Debug.WriteLine($"Sending Snapshot {ssCount}");
                cancellationToken.ThrowIfCancellationRequested();
                var random = Enumerable.Repeat(0, 700).Select(ii => randNum.Next(-1000, 1000));
                yield return random.ToArray();
                await Task.Delay(50, cancellationToken);
                ssCount++;
            }
            // ReSharper disable once IteratorNeverReturns
            // Returns with cancellation token
        }
    }
}
