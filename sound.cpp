#include "VoidTrack.h"

short int* rawPcmDataMusic;
ALCcontext *context;
ALCdevice *device;

inline void ignore_result(ssize_t t){}
void setupOpenAl(){
 	const char * devicename = alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);
	device = alcOpenDevice(devicename);

	//Create a context
	context=alcCreateContext(device,NULL);
 
	//Set active context
	alcMakeContextCurrent(context);
 
	// Clear Error Code
	alGetError();
}
   

unsigned int loadSoundFile(const char *file, bool music){
	//Loading wave file not using alut found on google
FILE* fp = NULL;
    fp = fopen(file, "r");
    if (!fp) {
        fclose(fp);
        return 0;
    }
        
    char* ChunkID  =new char[4];
    ChunkID[4] = '\0';
   ignore_result( fread(ChunkID, 4, sizeof(char), fp));
    if (strcmp(ChunkID, "RIFF")) {
        delete [] ChunkID;
        fclose(fp);
        return 0;
    }
    fseek(fp, 8, SEEK_SET);
    char* Format = new char[4];
     Format[4] = '\0';
    ignore_result(  fread(Format, 4, sizeof(char), fp));
        
    if (strcmp(Format, "WAVE")) {
        delete [] ChunkID;
        delete [] Format; 
        fclose(fp);
        return 0;
    }

    char* SubChunk1ID = new char[4];
    SubChunk1ID[4] = '\0';
     ignore_result( fread(SubChunk1ID, 4, sizeof(char), fp));
 
    if (strcmp(SubChunk1ID, "fmt ")) {
        delete [] ChunkID;
        delete [] Format;
        delete [] SubChunk1ID;
        fclose(fp);
        return 0;
    }
    
    unsigned int SubChunk1Size = 0;
     ignore_result( fread(&SubChunk1Size, 1, sizeof(unsigned int), fp));
    unsigned int SubChunk2Location = (unsigned int)ftell(fp) + SubChunk1Size;
    // -------------------------------------- THIS PART
 
    unsigned short AudioFormat = 0;
    ignore_result(  fread(&AudioFormat, 1, sizeof(unsigned short), fp));
    
    if (AudioFormat != 1) { // AudioFormat = 85, should be 1
        delete [] ChunkID;
        delete [] Format;
        delete [] SubChunk1ID;
        fclose(fp);
        return 0;
    }
 
    // --------------------------------------
 
    unsigned short NumChannels = 0;
     ignore_result( fread(&NumChannels, 1, sizeof(unsigned short), fp));
    unsigned int SampleRate =0 ;
     ignore_result( fread(&SampleRate, 1, sizeof(unsigned int), fp));
    
    fseek(fp, 34, SEEK_SET);
    
    unsigned short BitsPerSample = 0;
     ignore_result( fread(&BitsPerSample, 1, sizeof(unsigned short), fp));
    
    int ALFormat;
    if (NumChannels == 1 && BitsPerSample == 8) {
        ALFormat = AL_FORMAT_MONO8;
    } else if (NumChannels == 1 && BitsPerSample == 16) {
        ALFormat = AL_FORMAT_MONO16;
    } else if (NumChannels == 2 && BitsPerSample == 8) {
        ALFormat = AL_FORMAT_STEREO8;
    } else if (NumChannels == 2 && BitsPerSample == 16) {
        ALFormat = AL_FORMAT_STEREO16;
    } else {
        delete [] ChunkID;
        delete [] Format;
        delete [] SubChunk1ID;
        fclose(fp);
        return 0;
    }
    fseek(fp, SubChunk2Location, SEEK_SET);
    char* SubChunk2ID = new char[4];
    SubChunk2ID[4] = '\0';
    ignore_result(  fread(SubChunk2ID, 4, sizeof(char), fp));
    
    if (strcmp(SubChunk2ID, "data")) {
        delete [] ChunkID;
        delete [] Format;
        delete [] SubChunk1ID;
        delete [] SubChunk2ID;
        fclose(fp);
        return 0;
    }
    unsigned int SubChunk2Size;
     ignore_result( fread(&SubChunk2Size, 1, sizeof(unsigned int), fp)); 
    unsigned char* Data = new unsigned char[SubChunk2Size];
    
    ignore_result(  fread(Data, SubChunk2Size, sizeof(unsigned char), fp));
     if(music)
        rawPcmDataMusic = (short int*)Data;

    
    delete [] ChunkID;
    delete [] Format;
    delete [] SubChunk1ID;
    delete [] SubChunk2ID;
    fclose(fp);
     

unsigned int alSource;      
unsigned int buffer;
//create a source
alGenSources(1, &alSource);
 
//create  buffer
alGenBuffers(1, &buffer);
      alBufferData(buffer, ALFormat, Data,
                 SubChunk2Size, SampleRate);

      //assign the buffer to this source
alSourcei(alSource, AL_BUFFER,  buffer);
    return alSource;
}

void playSound(unsigned int alSource, bool loop){
	alSourcei(alSource,AL_LOOPING,loop);
	alSourcePlay(alSource);
}

void stopSound(unsigned int alSource){
	alSourceStop(alSource);
    alSourceRewind(alSource);
}

void pauseSound(unsigned int alSource){
	alSourcePause(alSource);
}

int getCurrentLoundnessOfMusic(){
    int offset;
    alGetSourcei(MUSIC, AL_SAMPLE_OFFSET, &offset);
return rawPcmDataMusic[offset ];
}

void closeOpenAL(){
    alcDestroyContext(context);
    alcCloseDevice(device);
}