#!/usr/bin/env dtrace -s

node$1:::
/pid==$1/
{
}
