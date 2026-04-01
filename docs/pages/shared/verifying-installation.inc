After installing UDUNITS-2, verify that the installation is working before building dependent software.

A correct installation requires the following components to be discoverable:

- the `udunits2` executable  
- the development headers (`udunits2.h`)  
- the UDUNITS-2 library (`libudunits2`)  
- the units database (`udunits2.xml`)

The [Installation Health Check](installation-health-check.html) guide provides commands and scripts that confirm these components are installed and accessible. It can quickly detect common issues such as missing headers, missing libraries, incorrect include or library paths, or a misconfigured units database.