[![pipeline status](https://gitlab.ethz.ch/se2021-kiss/zombiedice/badges/master/pipeline.svg)](https://gitlab.ethz.ch/se2021-kiss/zombiedice/-/commits/master) [![coverage report](https://gitlab.ethz.ch/se2021-kiss/zombiedice/badges/master/coverage.svg)](https://gitlab.ethz.ch/se2021-kiss/zombiedice/-/commits/master)

# Zombie Dice Project


## 1. Compile instructions
This project only works on UNIX systems (Linux / MacOS). We recommend using [Ubuntu](https://ubuntu.com/#download), as it offers the easiest way to setup wxWidgets. Therefore, we explain installation only for Ubuntu systems. The following was tested on a Ubuntu 20.4 system, but should also work for earlier versions of Ubuntu.

**Note:** If you create a virtual machine, we recommend to give the virtual machine at least 12GB of (dynamic) harddrive space (CLion and wxWidgets need quite a lot of space).

### 1.1 Prepare OS Environment

#### Ubuntu 20.4
The OS should already have git installed in order to download this repository. If not, you can use:
`sudo apt-get install git`

Execute the following commands in a console:
1. `sudo apt-get update`
2. `sudo apt-get install build-essential` followed by `sudo reboot`
3. if on virtual machine : install guest-additions (https://askubuntu.com/questions/22743/how-do-i-install-guest-additions-in-a-virtualbox-vm) and then `sudo reboot`
4. `sudo snap install clion --classic` this installs the latest stable CLion version
5. `sudo apt-get install libwxgtk3.0-gtk3-dev` this installs wxWidgets (GUI library used in this project)

#### Mac OS (Tested on 10.13)
We take no guarantee that the steps below are complete or deliver the desired effect. 

1. Install Xcode commandline tools: `xcode-select --install`
2. Install Homebrew: https://brew.sh/
3. `brew install wxmac`


### 1.2 Compile Code
1. Open Clion
2. Click `File > Open...` and there select the **/sockpp** folder of this project
3. Click `Build > Build all in 'Debug'`
4. Wait until sockpp is compiled (from now on you never have to touch sockpp again ;))
5. Click `File > Open...` select the **/cse-lama-example-project** folder
6. Click `Build > Build all in 'Debug'`
7. Wait until Lama-server, Lama-client and Lama-tests are compiled
