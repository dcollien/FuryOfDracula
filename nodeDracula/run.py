#!/usr/bin/python
"""
TODO: compile and run multiple games

"""

import subprocess
import sys

def runGame(  ):
   print sys.argv
   runArgs = [
	  "nodejs",
	  "../game_runner/runGame.js",
	  str(sys.argv[0]),
	  str(sys.argv[1]),
	  str(sys.argv[2]),
	  str(sys.argv[3]),
	  str(sys.argv[4])
   ]

   stdin = ""

   p = subprocess.Popen( runArgs,
	  stdin=subprocess.PIPE, stderr=subprocess.PIPE, stdout=subprocess.PIPE )


   print "Running games..."
   stdout, stderr = p.communicate( stdin )

   print stdout
   print stderr

runGame( )
