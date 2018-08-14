#ifndef AUDIO_H
#define AUDIO_H

#include <QVector>
#include <QThread>
#include <QWaitCondition>
#include <QMutex>

//#define INT16_MAX 0x7fff
//#define INT16_MIN (-INT16_MAX-1)

class QIODevice;
class QAudioOutput;

struct Sequence;

extern QAudioOutput* audio_output;
extern QIODevice* audio_io_device;

#define audio_ibuffer_size 192000
extern qint8 audio_ibuffer[audio_ibuffer_size];
extern int audio_ibuffer_read;
extern long audio_ibuffer_frame;
void clear_audio_ibuffer();

void init_audio();
void stop_audio();
int get_buffer_offset_from_frame(long frame);

class AudioSenderThread : public QThread {
	Q_OBJECT
public:
	AudioSenderThread();
	void run();
	void stop();
	QWaitCondition cond;
	bool close;
	QMutex lock;
private:
	QVector<qint16> samples;
	int send_audio_to_output(int offset, int max);
};

#endif // AUDIO_H
