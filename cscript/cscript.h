/*  cscript.h
    Copyright (C) 2015 Stu Mark
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>. */

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
