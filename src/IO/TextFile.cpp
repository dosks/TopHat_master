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

#include "TextFile.hpp"
#include "FileLineReader.hpp"
#include "ZipLineReader.hpp"

#include <assert.h>

TLineReader *
OpenTextFile(const TCHAR *path, Charset cs)
{
  assert(path != nullptr);

  FileLineReader *reader = new FileLineReader(path, cs);
  if (reader == nullptr)
    return nullptr;

  if (!reader->error())
    return reader;

  delete reader;

  ZipLineReader *zip_reader = new ZipLineReader(path, cs);
  if (zip_reader == nullptr)
    return nullptr;

  if (!zip_reader->error())
    return zip_reader;

  delete zip_reader;

  return nullptr;
}
