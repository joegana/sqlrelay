#ifndef SQLRCONNECTION_IPC_H
#define SQLRCONNECTION_IPC_H

#include <rudiments/semaphoreset.h>
#include <rudiments/sharedmemory.h>
#ifdef SERVER_DEBUG
	#include <rudiments/logger.h>
#endif
#include <defines.h>

class ipc {
	public:
			ipc();
			~ipc();

		bool	initialized();

		#ifdef SERVER_DEBUG
		void	setDebugLogger(logger *dl);
		#endif

		bool		createSharedMemoryAndSemaphores(char *tmpdir,
								char *id);

		void		acquireAnnounceMutex();
		shmdata		*getAnnounceBuffer();
		void		signalListenerToRead();
		void		waitForListenerToFinishReading();
		void		releaseAnnounceMutex();

		void		acquireConnectionCountMutex();
		unsigned int	*getConnectionCountBuffer();
		void		signalScalerToRead();
		void		releaseConnectionCountMutex();

		void		acquireSessionCountMutex();
		unsigned int	*getSessionCountBuffer();
		void		releaseSessionCountMutex();

	private:
		semaphoreset	*semset;
		sharedmemory	*idmemory;

		#ifdef SERVER_DEBUG
		logger		*dl;
		#endif
};

#endif
