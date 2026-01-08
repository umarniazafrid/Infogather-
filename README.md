## Versioning

Infogather++ follows **Semantic Versioning (SemVer)**:

- **MAJOR** version changes indicate architectural or breaking changes
- **MINOR** versions add new features in a backward-compatible way
- **PATCH** versions include bug fixes and minor improvements

### Current Version
- **v1.0.0** — Initial release with core reconnaissance features

### Stability Notice
Early versions focus on building a reliable and extensible recon foundation.
Feature depth and coverage will expand gradually in future releases.



KALI LINUX INSTRUCTIONS
======================

This tool is designed and tested on Kali Linux.

REQUIREMENTS
------------
- Kali Linux (or any modern Linux distro)
- g++ (C++ compiler)
- whois utility

INSTALL DEPENDENCIES
--------------------
sudo apt update

sudo apt install g++ whois -y

COMPILE
-------
cd Infogather- 

make

RUN
---
sudo ./infogather++

NOTE
----
Root privileges are required for certain network operations
such as ICMP-based host checks.


