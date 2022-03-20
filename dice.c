#include <unistd.h>
#include <stdlib.h>

#define SIDES 6

size_t	t_strlen(char *str) {
	size_t i;

	i = 0;
	while (str[i] != '\0') {
		i++;
	}
	return i;
}

char	*ztoa(size_t nbr) {
	char	*a;
	size_t	len;
	int	i;

	if (nbr == 0) {
		a = (char *)malloc(sizeof(char) * 2);
		a[0] = '0';
		a[1] = '\0';
		return a;
	}
	len = 0;
	i = nbr;
	while (i != 0) {
		len++;
		i /= 10;
	}
	a = (char *)malloc(sizeof(char) * (len + 1));
	a[len] = '\0';
	i = nbr % 10;
	while (nbr != 0) {
		a[--len] = '0' + i;
		nbr /= 10;
		i = nbr % 10;
	}
	return a;
}

void	print(size_t i, size_t v) {
	char	str[i];
	char	*z;
	size_t	l;

	l = 0;
	while (l < i) {
		str[l] = '|';
		l++;
	}
	z = ztoa(v);
	write(1, str, i);
	write(1, " ", 1);
	write(1, z, t_strlen(z));
	write(1, "\n", 1);
	free(z);
}

void	chances(size_t *ch, size_t v, size_t dice) {
	size_t i;

	if (dice == 0) {
		ch[v - 1] += 1;
		return;
	}
	i = 0;
	while (i < SIDES) {
		i++;
		chances(ch, v + i, dice - 1);
	}
}

void	zero(size_t *array, size_t size) {
	while (size) {
		size--;
		array[size] = 0;
	}
}

void	chance(size_t dice) {
	size_t max;
	size_t *ch;

	max = SIDES * dice;
	ch = (size_t *)malloc(sizeof(size_t) * max);
	zero(ch, max);
	chances(ch, 0, dice);
	while (max) {
		max--;
		print(ch[max], max + 1);
	}
	free(ch);
}

int	input(int argc, char *argv[]) {
	int i;

	if (argc != 2) return -1;
	return atoi(argv[1]);
}

int	main(int argc, char *argv[]) {
	int dice;

	if ((dice = input(argc, argv)) > 0) chance((size_t)dice);
	else write(1, "\n", 1);
	return 0;
}
