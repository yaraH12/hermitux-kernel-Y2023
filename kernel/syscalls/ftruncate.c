#include <hermit/syscall.h>
#include <hermit/logging.h>
#include <hermit/minifs.h>
#include <asm/page.h>
#include <asm/uhyve.h>

typedef struct {
	int fd;
	off_t length;
	int ret;
} _attribute_((packed)) uhyve_ftruncate_t;

int sys_ftruncate(int fd, off_t length) {
	uhyve_ftruncate_t arg;

	arg.fd = fd;
	arg.length = length;
	arg.ret = -1;
	uhyve_send(UHYVE_PORT_FTRUNCATE, (unsigned)virt_to_phys((size_t)&arg));

	return arg.ret;
}