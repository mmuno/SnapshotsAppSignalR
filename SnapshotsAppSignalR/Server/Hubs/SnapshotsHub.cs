﻿// ReSharper disable UnusedMember.Global

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

        /// <summary>
        /// Starts streaming snapshots signal
        /// </summary>
        /// <param name="timeSpan">Time Span in milliseconds</param>
        /// <param name="selectedChannels">Selected Channels</param>
        /// <param name="cancellationToken">Cancellation token</param>
        /// <returns></returns>
        public async IAsyncEnumerable<short[]> SnapshotsStream(
            int timeSpan,
            HashSet<int> selectedChannels,
            [EnumeratorCancellation]
            CancellationToken cancellationToken)
        {
            if (selectedChannels.Count == 0)
            {
                Debug.WriteLine($"No Channels selected");
                yield return null;
            }


            var nSamples = timeSpan * 14;
            var randNum = new Random();
            var ssCount = 0;
            while (true)
            {
                var index0 = 0;
                var snapshotsPacket = new short[selectedChannels.Count * nSamples];
                cancellationToken.ThrowIfCancellationRequested();
                foreach (var channel in selectedChannels)
                {
                    Debug.WriteLine($"Sending Snapshot {ssCount}, timespan {timeSpan}, nSamples {nSamples}, channelId {channel}");
                    for (int i = 0; i < nSamples; i++)
                    {
                        snapshotsPacket[index0] = (short)randNum.Next(-1000, 1000);
                        index0++;
                    }
                }

                yield return snapshotsPacket;
                await Task.Delay(timeSpan, cancellationToken);
                ssCount++;
            }
            // ReSharper disable once IteratorNeverReturns
            // Returns with cancellation token
        }
    }
}
