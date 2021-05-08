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
repo][hackchi code] and adapted to C++.

It's not super fast, there are faster ways of doing CRC32 that aren't a byte at
a time. But I didn't care.

I also used indirection (via a config file) becaue I'm lazy. I didn't want to
generate the table each time because I was (dumbly) worried about performance,
so originally I had the binary reading each filename from args. But then I spent
a few minutes figuring out max arglength and quoting and just decided to dump
filenames into a config file. For reference, you can do that with something
like:

`find $PWD -name "*.smc" > files.config`

[SNES Classic]:https://en.wikipedia.org/wiki/Super_NES_Classic_Edition
[Hackchi2]:https://github.com/ClusterM/hakchi2
[Hackchi2 CE]:https://github.com/TeamShinkansen/Hakchi2-CE
[hackchi code]:https://github.com/ClusterM/hakchi2/blob/stable/Apps/NesMiniApplication.cs#L258
