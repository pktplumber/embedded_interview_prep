# Implement `malloc` and `free` for an Embedded System in C

### Constraints
- 128 KB RAM
- Many small allocations
- Occasional large buffer allocations
- Long system uptime

### Follow-ups
- How do you avoid fragmentation?
- How do you detect memory leaks?
- What happens if allocation fails?
- Would you even allow malloc in production firmware?