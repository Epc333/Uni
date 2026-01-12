#ifndef __ERRNO_H__
#define __ERRNO_H__

#define EBADF 9
#define EAGAIN 11
#define EFAULT 14
#define EINVAL 22
#define ENOSYS 38

#define ESEMNOPR 200 // Thread no es propietario del semaforo
#define ESEMINAD 201 //Puntero de semáforo inválido (fuera de rango de sem_vec)
#define ESEMNOBL 202 // No hay procesos a desbloquear


#endif  /* __ERRNO_H__ */