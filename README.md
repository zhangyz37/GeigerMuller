# GeigerMuller

GEANT simulation of a Geiger-Muller counter, for demonstrating abilities of Geant4.

## Authors

* **Balázs Demeter** - *University of Debrecen* - [E-mail](mailto:balazsdemeter92@gmail.com)
* **Balázs Ujvári** - *University of Debrecen* - [E-mail](mailto:balazs.ujvari@science.unideb.hu)

## Summary

In 2015, GEANT course was held in Wigner Research Centre for Physics at Csillebérc, Hungary by me and my mentor, Balázs Ujvári. 
This GM counter simulation's previous version was part of the course.

## Download and build

### Requirements

* Linux (Tested on Ubuntu 16.04 LTS)

* Qt4 (Tested on version 5.9.1) 

* GEANT 4.10.03 or newer

* CLHEP 2.3.4.4 or newer

### Download Link

Via Git:

```
git clone https://github.com/dbalazs92/GeigerMuller.git
```

Direct link:

```
https://github.com/dbalazs92/GeigerMuller/archive/master.zip
```

### Build

In the directory of program (GeigerMuller), open a terminal window and enter:

```
chmod 744 setup.sh
```

After giving the necessary permissions for setup script, run:

```
./setup.sh
``` 

### Running the simulation
 
#### Run in batch mode

After build, in the directory of build (emcal_build), open a terminal window and enter:

```
./DB_EMCal <numberofevents> <physicslist> <typeofcut> 
```

#### Run in interactive mode

After build, in the directory of program (DB_EMCal), open a terminal window and enter:

```
./interactive.sh
```

#### Working EM PhysicsList (PL) and deexcitation cut combos

* PL #0: 2,3

* PL #1: 3

* PL #2: 2,3

* PL #3: 1,2,3

* PL #4: 0,1,2,3

* PL #5: 1,2,3

## Updates

* 2017/10/10 - 'v2.0' - Creation of reloaded version and it's repository

* 2015/09/31 - 'v1.0' - Creation of program
