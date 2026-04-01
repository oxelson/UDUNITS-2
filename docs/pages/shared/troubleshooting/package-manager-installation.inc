Most installation issues when installing **UDUNITS-2 using system package managers** fall into a few common categories.

Examples of package managers include **apt**, **dnf/yum**, **Homebrew**, and **MacPorts**.

Before using the troubleshooting tables below, run the checks in the [UDUNITS-2 Installation Health Check](installation-health-check.html) to verify that the UDUNITS-2 executable, headers, libraries, and units database are correctly installed.

### Development Headers Missing

| Symptom | Cause | Diagnosis | Fix |
| ------ | ----- | --------- | --- |
| `udunits2.h: No such file or directory` | Development headers not installed | Check installed packages | Install development package (`libudunits2-dev`, `udunits2-devel`, etc.) |
| Python/R packages fail detecting UDUNITS-2 | Runtime package installed but headers missing | Inspect build logs for `udunits2.h` errors | Install the UDUNITS-2 development package |

### Package Metadata Issues

| Symptom | Cause | Diagnosis | Fix |
| ------ | ----- | --------- | --- |
| `Package 'udunits2' not found` from `pkg-config` | pkg-config metadata missing | Run `pkg-config --list-all | grep udunits` | Install development package containing `udunits2.pc` |

### Library Linking Issues

| Symptom | Cause | Diagnosis | Fix |
| ------ | ----- | --------- | --- |
| `ld: cannot find -ludunits2` | Linker cannot find the UDUNITS-2 library | Run `pkg-config --libs udunits2` | Install development package or add correct `-L` path |
| `undefined reference to ut_*` functions | Program not linking against UDUNITS-2 | Inspect compile command | Add `-ludunits2` to linker flags |

### Runtime Issues

| Symptom | Cause | Diagnosis | Fix |
| ------ | ----- | --------- | --- |
| Runtime error loading `libudunits2.so` / `.dylib` | Dynamic linker cannot find library | Run `ldd program` or `otool -L program` | Update linker cache (`ldconfig`) or adjust library paths |
| `Couldn't open units database` | XML database path overridden or missing | Check `echo $UDUNITS2_XML_PATH` | Unset variable or reinstall package |

### Environment Conflicts

| Symptom | Cause | Diagnosis | Fix |
| ------ | ----- | --------- | --- |
| Software builds but behaves unexpectedly | Multiple UDUNITS-2 installations present | Run `which udunits2` and inspect linked libraries | Remove duplicate installs or ensure consistent include/library paths |
