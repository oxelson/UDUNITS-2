Most **Conda installation issues** fall into a small number of common categories.

Before using the troubleshooting tables below, run the checks in the [UDUNITS-2 Installation Health Check](installation-health-check.html) to verify that the UDUNITS-2 executable, headers, libraries, and units database are correctly installed.

### Package Missing From Environment

| Symptom | Cause | Diagnosis | Fix |
| ------ | ----- | --------- | --- |
| `udunits2.h: No such file or directory` | UDUNITS-2 not installed in environment | Run `conda list | grep udunits` | Install with `conda install udunits2` |

### Environment Activation Issues

| Symptom | Cause | Diagnosis | Fix |
| ------ | ----- | --------- | --- |
| Python package build fails detecting UDUNITS-2 | Environment not activated | Run `conda info --envs` | Activate environment with `conda activate <env>` |

### Library Loading Issues

| Symptom | Cause | Diagnosis | Fix |
| ------ | ----- | --------- | --- |
| `DLL load failed` or `Library not loaded: libudunits2` | Environment library paths inactive | Inspect linked libraries | Ensure environment is activated before running program |

### Language Binding Issues

| Symptom | Cause | Diagnosis | Fix |
| ------ | ----- | --------- | --- |
| R package `units` fails to install | UDUNITS-2 headers missing in environment | Inspect installation logs | Install `udunits2` inside environment |

### Path Conflicts

| Symptom | Cause | Diagnosis | Fix |
| ------ | ----- | --------- | --- |
| Program links against system UDUNITS-2 | System paths appear before Conda paths | Inspect libraries with `ldd` or `otool -L` | Ensure Conda environment appears first in `PATH` |

### IDE Environment Issues

| Symptom | Cause | Diagnosis | Fix |
| ------ | ----- | --------- | --- |
| Package works in terminal but not IDE | IDE not using Conda environment | Check interpreter settings | Configure IDE to use correct environment |

### Rare Runtime Issues

| Symptom | Cause | Diagnosis | Fix |
| ------ | ----- | --------- | --- |
| Runtime unit parsing errors | XML database not found in environment | Locate `udunits2.xml` | Ensure `UDUNITS2_XML_PATH` is not overriding correct path |
