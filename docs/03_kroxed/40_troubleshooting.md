---
content_title: Kroxed Troubleshooting
---

## How to solve the error "Failed to lock access to wallet directory; is another `kroxed` running"?

Since `clroxe` may auto-launch an instance of `kroxed`, it is possible to end up with multiple instances of `kroxed` running. That can cause unexpected behavior or the error message above.

To fix this issue, you can terminate all running `kroxed` instances and restart `kroxed`. The following command will find and terminate all instances of `kroxed` running on the system:

```sh
pkill kroxed
```
