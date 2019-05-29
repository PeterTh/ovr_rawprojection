# ovr_rawprojection
Basic OpenVR program to read out the GetProjectionRaw return values for both eyes.

The idea is to use the results to compare the rendered FoV and binocular overlap of various HMDs, as in this table:
https://docs.google.com/spreadsheets/d/1q7Va5Q6iU40CGgewoEqRAeypUa1c0zZ86mqR8uIyDeE

## Usage

Just run the program. It should start your VR runtime if it is not already running, and then print some information.

Example output:
```
Number of tracked HMDs detected: 1

        HMD manufacturer: Pimax VR, Inc.
     HMD tracking system: aapvr
               HMD model: Pimax 8K
Reading property "HMD hardware revision" failed: TrackedProp_UnknownProperty
Reading property "HMD driver version" failed: TrackedProp_UnknownProperty

-----------------------------------------------

Results:
Eye_Left:  -2.76923,  0.94542, -1.63580,  1.63580
Eye_Right: -0.94542,  2.76923, -1.63580,  1.63580

-----------------------------------------------

NOTE: please ensure that the following conditions are met
      if you plan to submit your results for inclusion in
      the overall comparison spreadsheet:
 - If the HMD has an eye relief setting, set it as close
   to the eye position as possible.
 - If the HMD has an IPD setting, set it to the average
   human IPD of 64mm.

How to contribute:
  *If* your VR HMD is not included here:
  https://docs.google.com/spreadsheets/d/1q7Va5Q6iU40CGgewoEqRAeypUa1c0zZ86mqR8uIyDeE
  then please post your results here:
  https://metacouncil.com/threads/the-metaverse-vr-thread-hardware-software-etc-all-platforms.956
  or send them to DuranteA on reddit. Thanks!
```

## Building It

I'm too lazy to add a build process sufficiently well-made as to not be more trouble than it's worth. The program is a single translation unit and you need to link it to the OpenVR library. That's it.
