# clvcode

## Usage:
```
clvcode <config-file>

  config-file: single filename per line, to calculate sums for
  output: log lines with filename + clover code (assumes SNES)
```

## Why?
I have an [SNES Classic][] that I upgraded from [Hackchi2][] to [Hackchi2 CE][].
When I did it, I accidentally cleared out all my ROMs on the device. Luckily I
had them still on my computer, but as `.7z` archives that contained lots of
different versions of the games. Particularly for translated games (FFV, Tales
of Phantasia, etc.) which translation I picked wasn't obvious.

After re-installing and picking reasonable defaults, Hackchi2 CE showed me I had
a set of stranded save states. Those states are linked to the games by some
CRC32-based code. So to figure out which ones I was missing, I unzipped all the
archives and ran this binary to find the equivalent codes.

## Implementation notes
I'm mostly familiar with C++/`absl` so used it here.

The specific CRC32 and "code" generating logic I took from the [Hackchi
repo][hackchi code];

[SNES Classic]:https://en.wikipedia.org/wiki/Super_NES_Classic_Edition
[Hackchi2]:https://github.com/ClusterM/hakchi2
[Hackchi2 CE]:https://github.com/TeamShinkansen/Hakchi2-CE
[hackchi code]:https://github.com/ClusterM/hakchi2/blob/stable/Apps/NesMiniApplication.cs#L258
