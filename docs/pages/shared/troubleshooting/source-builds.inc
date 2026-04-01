When building **UDUNITS-2 from source**, installation issues typically occur during one of the following stages:

Dependencies → Build Configuration → Compilation and Linking → Runtime → Environment Conflicts → Platform-Specific Issues

Before using the troubleshooting tables below, run the checks in the [UDUNITS-2 Installation Health Check](installation-health-check.html) to verify that the UDUNITS-2 executable, headers, libraries, and units database are correctly installed.

### Dependency Issues

These errors occur when required libraries cannot be found during the configuration stage.

| Symptom | Cause | Diagnosis | Fix |
| ------ | ----- | --------- | --- |
| `configure: cannot find EXPAT function XML_StopParser` | Expat library missing or not detected | Inspect `config.log` | Install the Expat development package |
| `expat.h: No such file or directory` | Expat headers not installed | Search include directories | Install Expat development headers |
| `ld: cannot find -lexpat` | Linker cannot locate Expat library | Check library paths | Install Expat library or add `-L/path/to/expat/lib` |

### Build Configuration Issues

These problems occur during the **configure or CMake stage** when paths or environment variables are not set correctly.

| Symptom | Cause | Diagnosis | Fix |
| ------ | ----- | --------- | --- |
| Configure fails to detect dependencies | Environment variables not configured correctly | Inspect `config.log` | Set `CPPFLAGS` and `LDFLAGS` appropriately |
| `udunits2.h: No such file or directory` | Headers installed in non-standard location | Locate installed headers | Add `-I/path/to/include` |

### Compilation And Linking Issues

These errors occur when compiling or linking applications against UDUNITS.

| Symptom | Cause | Diagnosis | Fix |
| ------ | ----- | --------- | --- |
| `ld: cannot find -ludunits2` | Library path not visible to linker | Inspect library install location | Add `-L/path/to/lib` |
| `undefined reference to ut_*` functions | Program not linking against UDUNITS-2 | Inspect compile command | Add `-ludunits2` |

### Runtime Issues

These problems appear after successful compilation when the program is executed.

| Symptom | Cause | Diagnosis | Fix |
| ------ | ----- | --------- | --- |
| Runtime error loading `libudunits2.so` | Library path not registered with dynamic linker | Run `ldd program` | Run `ldconfig` or update `LD_LIBRARY_PATH` |
| `Couldn't open units database` | XML units database not found | Search installation directory for `udunits2.xml` | Set `UDUNITS2_XML_PATH` |

### Environment and Installation Conflicts

These issues occur when multiple versions of UDUNITS-2 exist on the system.

| Symptom | Cause | Diagnosis | Fix |
| ------ | ----- | --------- | --- |
| Program links against wrong UDUNITS-2 version | Multiple installations present | Inspect linked libraries with `ldd` | Remove duplicate installations or adjust include/library paths |

### Windows-Specific Issues

These problems occur when building UDUNITS-2 using **Visual Studio or Windows toolchains**.

| Symptom | Cause | Diagnosis | Fix |
| ------ | ----- | --------- | --- |
| `udunits2.h` not found in Visual Studio | Include path not configured | Check project include directories | Add UDUNITS-2 include directory |
| `udunits2.lib` not found during linking | Import library not configured | Inspect linker settings | Add library directory and dependency |
| `libudunits2.dll` not found at runtime | DLL not in system search path | Run program from command prompt | Add directory to `PATH` or copy DLL next to executable |
