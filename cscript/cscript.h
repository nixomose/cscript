#ifndef CSCRIPT_H_
#define CSCRIPT_H_

class cscript
  {
  public:
    cscript();
    virtual ~cscript();
    int go(int num, char *opts[], char *link_options);

  private:

    void hey_killer(const char *binname);


    int pid;
    int pipefds[2];
    FILE *f;
    FILE *gcc;

  };

#endif /* CSCRIPT_H_ */
