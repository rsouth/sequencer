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
#include "Interaction.h"

Interaction::Interaction(int index, Participant& from_participant, Participant& to_participant,
                         const std::string& message, bool is_reply, bool is_async):
	index_(index),
	from_participant_(std::move(from_participant)),
	to_participant_(std::move(to_participant)),
	message_(message), is_reply_(is_reply), is_async_(is_async)
{
}

bool Interaction::is_self_referential() const
{
	return this->from_participant_.get_name() == this->to_participant_.get_name();
}

std::string Interaction::get_message() const
{
	return this->message_;
}

Participant Interaction::get_from() const
{
	return this->from_participant_;
}

Participant Interaction::get_to() const
{
	return this->to_participant_;
}

int Interaction::get_index() const
{
	return this->index_;
}

bool Interaction::is_reply() const
{
	return this->is_reply_;
}

bool Interaction::is_async() const
{
	return this->is_async_;
}