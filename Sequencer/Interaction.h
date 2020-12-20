/*
 *     Copyright (C) 2020 rsouth (https://github.com/rsouth)
 *
 *     This program is free software: you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation, either version 3 of the License, or
 *     (at your option) any later version.
 *
 *     This program is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 *
 *     You should have received a copy of the GNU General Public License
 *     along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#pragma once
#include "Participant.h"

class Interaction {
public:
  Interaction(int index, Participant& from_participant, Participant& to_participant, const std::string& message,
              bool is_reply = false, bool is_async = false);

  std::string get_message() const;

  Participant get_from() const;

  Participant get_to() const;

  int get_index() const;

  bool is_self_referential() const;

  bool is_reply() const;

  bool is_async() const;

private:
  int index_;
  Participant from_participant_;
  Participant to_participant_;
  std::string message_;
  bool is_reply_;
  bool is_async_;
};
