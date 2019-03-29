## Additions to crn.cpp from ManagedCrunch/src/crunch

Created a new wrapper function `crn_set_memory_callbacks` (wrapping `crnd::crnd_set_memory_callbacks`)

Build instructions use DaemonEngine/crunch master, not Binomial or Unity's crunch

## Linux build

Built on CentOS 6.10 -- which is deliberately ancient (GCC 4!)

Minor adjustments may or may not be wise for building on more modern platforms

See `linux_build.txt`. It's vaguely a shell script.

## Mac build

TBD

## Win (MINGW32) build

TBD

