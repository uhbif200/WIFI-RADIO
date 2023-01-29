#include "gpioirqt.h"

#define SYSFS_GPIO_DIR "/sys/class/gpio"
#define POLL_TIMEOUT (3 * 1000) /* 3 seconds */
#define MAX_BUF 64
#define DEBOUNCE_TIME 0

using namespace std;

int gpio_export(unsigned int gpio)
{
	int fd, len;
	char buf[MAX_BUF];

	fd = open(SYSFS_GPIO_DIR "/export", O_WRONLY);
	if (fd < 0) {
		perror("gpio/export");
		return fd;
	}

	len = snprintf(buf, sizeof(buf), "%d", gpio);
	write(fd, buf, len);
	close(fd);

	return 0;
}

/****************************************************************
 * gpio_unexport
 ****************************************************************/
int gpio_unexport(unsigned int gpio)
{
	int fd, len;
	char buf[MAX_BUF];

	fd = open(SYSFS_GPIO_DIR "/unexport", O_WRONLY);
	if (fd < 0) {
		perror("gpio/export");
		return fd;
	}

	len = snprintf(buf, sizeof(buf), "%d", gpio);
	write(fd, buf, len);
	close(fd);
	return 0;
}

/****************************************************************
 * gpio_set_dir
 ****************************************************************/
int gpio_set_dir(unsigned int gpio, unsigned int out_flag)
{
	int fd, len;
	char buf[MAX_BUF];

	len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR  "/gpio%d/direction", gpio);

	fd = open(buf, O_WRONLY);
	if (fd < 0) {
		perror("gpio/direction");
		return fd;
	}

	if (out_flag)
		write(fd, "out", 4);
	else
		write(fd, "in", 3);

	close(fd);
	return 0;
}

/****************************************************************
 * gpio_set_value
 ****************************************************************/
int gpio_set_value(unsigned int gpio, unsigned int value)
{
	int fd, len;
	char buf[MAX_BUF];

	len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio);

	fd = open(buf, O_WRONLY);
	if (fd < 0) {
		perror("gpio/set-value");
		return fd;
	}

	if (value)
		write(fd, "1", 2);
	else
		write(fd, "0", 2);

	close(fd);
	return 0;
}

/****************************************************************
 * gpio_get_value
 ****************************************************************/
int gpio_get_value(unsigned int gpio, unsigned int *value)
{
	int fd, len;
	char buf[MAX_BUF];
	char ch;

	len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio);

	fd = open(buf, O_RDONLY);
	if (fd < 0) {
		perror("gpio/get-value");
		return fd;
	}

	read(fd, &ch, 1);

	if (ch != '0') {
		*value = 1;
	} else {
		*value = 0;
	}

	close(fd);
	return 0;
}


/****************************************************************
 * gpio_set_edge
 ****************************************************************/

int gpio_set_edge(unsigned int gpio, char *edge)
{
	int fd, len;
	char buf[MAX_BUF];

	len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/edge", gpio);

	fd = open(buf, O_WRONLY);
	if (fd < 0) {
		perror("gpio/set-edge");
		return fd;
	}

	write(fd, edge, strlen(edge) + 1);
	close(fd);
	return 0;
}

/****************************************************************
 * gpio_fd_open
 ****************************************************************/

int gpio_fd_open(unsigned int gpio)
{
	int fd, len;
	char buf[MAX_BUF];

	len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio);

	fd = open(buf, O_RDONLY | O_NONBLOCK );
	if (fd < 0) {
		perror("gpio/fd_open");
	}
	return fd;
}

/****************************************************************
 * gpio_fd_close
 ****************************************************************/

int gpio_fd_close(int fd)
{
	return close(fd);
}

/****************************************************************
 * Main
 ****************************************************************/
int start_irq(int gpionum[],int gpionumSize, void (*update)())
{
	struct pollfd fdset[gpionumSize + 1];
	int nfds = gpionumSize + 1;
	int gpio_fd[gpionumSize], timeout, rc;
	char *buf[MAX_BUF];
	unsigned int gpio[gpionumSize];
	int len;
	int val;
  for(int i = 0; i < gpionumSize; i++){
    gpio[i] = gpionum[i];
    gpio_export(gpio[i]);
  	gpio_set_dir(gpio[i], 0);
  	gpio_set_edge(gpio[i], "both");
  	gpio_fd[i] = gpio_fd_open(gpio[i]);
  }


	timeout = POLL_TIMEOUT;

	time_t last_interrupt_time = 0;
	time_t interrupt_time = time(NULL);

	while (1) {
		memset((void*)fdset, 0, sizeof(fdset));

		// fdset[0].fd = STDIN_FILENO;								//interrupt init for command line
		// fdset[0].events = POLLIN;

    for(int i = 0; i < gpionumSize; i++){			//interrupts init for all gpio
      fdset[i].fd = gpio_fd[i];
  		fdset[i].events = POLLPRI;
    }

		rc = poll(fdset, nfds, timeout);

		if (rc < 0) {
			printf("\npoll() failed!\n");
			return -1;
		}

		if (rc == 0) {
			printf(".");
		}

    for(int i = 0; i < gpionumSize; i++){
      if (fdset[i].revents & POLLPRI) {
        lseek(fdset[i].fd, 0, SEEK_SET);
        len = read(fdset[i].fd, buf, MAX_BUF);
				//printf("succeess interrupt\n");
				update();
        	// If interrupts come faster than 200ms, assume it's a bounce and ignore
        	// time_t interrupt_time = time(NULL); //johoho
          //printf("\npoll() GPIO %i interrupt occurred\n", gpio[i]);
          //printf("\tread value: '%c'\n", buf[0]);
          //last_interrupt_time = interrupt_time;
          //fcnPtr(disp);
        //printf("%i\n",difftime);
        //last_interrupt_time = interrupt_time;
      }
    }

		// if (fdset[0].revents & POLLIN) {
		// 	(void)read(fdset[0].fd, buf, 1);
		// 	//printf("\npoll() stdin read 0x%2.2X\n", (unsigned int) buf[0]);
		// }
		fflush(stdout);
	}

  for (int i = 0; i < gpionumSize; i++){
    gpio_fd_close(gpio_fd[i]);
  }

	return 0;
}


// int main(){
// 	int size = 6;
//   int gpioarr[size] = {3,11,17,16,2,15};
//
//
//   start_irq(gpioarr, size);
// }
