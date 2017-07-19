#include <ApplicationServices/ApplicationServices.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
  OSErr rc;
  SpeechChannel channel;
  VoiceSpec vs;
  int voice;
  char *text = "What do you want me to say?";

  if (!argv[1]) {voice = 1;} else {voice = atoi(argv[1]); }
  if (argc == 3) {text = argv[2];}

  rc = GetIndVoice(voice, &vs);
  rc = NewSpeechChannel(&vs, &channel);
  rc = SpeakText(channel, text, strlen(text));
  if(rc) { fprintf(stderr, "Unable to speak!/n"); exit(1);}
   exit(0);
}
