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
	  "game_runner/runGame.js",
	  "hunter/hunters/mrDrunk/mrDrunk",
	  "hunter/hunters/mrDrunk/mrDrunk",
	  "hunter/hunters/mrDrunk/mrDrunk",
	  "hunter/hunters/mrDrunk/mrDrunk",
          ""
   ]

   stdin = ""

   p = subprocess.Popen( runArgs,
	  stdin=subprocess.PIPE, stderr=subprocess.PIPE, stdout=subprocess.PIPE )


   print "Running games..."
   stdout, stderr = p.communicate( stdin )

   print stdout
   print stderr

runGame( )
