# Changelog
All notable changes to this project will be documented in this file.

The format is based on Keep a Changelog,
and this project follows Semantic Versioning (SemVer).

---

## [v1.0.0] – Initial Release
### Added
- Multithreaded TCP port scanning (common service ports)
- Passive OS fingerprinting using TTL heuristics
- HTTP banner grabbing (HEAD request)
- WHOIS enumeration
- Controlled scan timing with jitter
- Automatic JSON-based recon report generation
- Modular C++ project structure (scanner / reporting separation)
- Kali Linux–ready build system (Makefile)

### Notes
- This release focuses on **foundational reconnaissance**
- No raw packet crafting or exploit logic included
- Designed as a stable base for future extensions

---

## [Unreleased]
- Planned improvements and feature expansions for v1.1.x
