/*
Copyright_License {

  Top Hat Soaring Glide Computer - http://www.tophatsoaring.org/
  Copyright (C) 2000-2016 The Top Hat Soaring Project
  A detailed list of copyright holders can be found in the file "AUTHORS".

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
}
*/

#ifndef XCSOAR_FILE_CACHE_HPP
#define XCSOAR_FILE_CACHE_HPP

#include <stdio.h>
#include <tchar.h>

class FileCache {
  TCHAR *cache_path;
  size_t cache_path_length;

public:
  FileCache(const TCHAR *_cache_path);
  ~FileCache();

protected:
  size_t PathBufferSize(const TCHAR *name) const;
  const TCHAR *MakeCachePath(TCHAR *buffer, const TCHAR *name) const;

public:
  void Flush(const TCHAR *name);
  FILE *Load(const TCHAR *name, const TCHAR *original_path);

  FILE *Save(const TCHAR *name, const TCHAR *original_path);
  bool Commit(const TCHAR *name, FILE *file);
  void Cancel(const TCHAR *name, FILE *file);
};

#endif
