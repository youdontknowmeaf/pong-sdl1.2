   [big_fury]
  888888888    8888  888888888888  8888     888888888     8888      8888   888888888
8888888888888  8888  888888888888  8888   8888888888888   8888      8888 8888888888888
8888     8888              88888         8888       8888  8888      8888 8888     8888
888888888      8888      888888    8888 8888         8888 8888      8888 888888888
  8888888888   8888     88888      8888 8888         8888 8888      8888   88888888888
       888888  8888   88888        8888 8888         8888 8888      8888         888888
8888      8888 8888  88888         8888  8888       8888  8888      8888 8888      8888
8888888888888  8888 88888888888888 8888   8888888888888    888888888888  8888888888888
  8888888888   8888 88888888888888 8888     888888888       8888888888     8888888888

CDI4DC
======

Version : v0.2b
(C)reated by [big_fury]SiZiOUS
http://sbibuilder.shorturl.com/

I) What's that
--------------

This proggy was written in order to replace the old (but good) Xeal's bin2boot.

It generates a *REAL* valid CDI selfboot file (e.g. a mountable CDI into virtual drives)
from a MSINFO'ed 11702 ISO.

The resulting CDI file is ready to burn, similar if you have used the ECHELON selfboot kit.

II) How to use it
-----------------

You need mkisofs from cdrtools and an ip.bin insertor. Just generate your iso with the
same command as the ECHELON tutorial :

mkisofs -C 0,11702 -V YOUR_VOLUME_NAME -joliet -rock -l -o YOUR_ISO.ISO YOUR_SOURCE_DIRECTORY

Don't forget to insert an ip.bin in the generated ISO. You can use ipinj in this package.

Then, you can use cdi4dc. Type this command :

Syntax: cdi4dc <input.iso> <output.cdi>

The result will be a valid CDI file.

So to recapitulate :
1. mkisofs -C 0,11702 -V YOUR_VOLUME_NAME -joliet -rock -l -o YOUR_ISO.ISO YOUR_SOURCE_DIRECTORY
2. ipins ip.bin YOUR_ISO.ISO
3. cdi4dc YOUR_ISO.ISO SELFBOOT.CDI

III) Credits
-------------

This proggy's dedicaced to Ron - Today it's the 6 july, happy bday amigo
Greetings to Xeal, DeXT, Heiko Eissfeldt and Joerg Schilling for libedc

Bugs report : Fackue

SiZ! for Dreamcast-Scene 2006... The legend will never die