/* Copyright 2013 David Axmark

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

/*
 * Link.cpp
 */

#include "Link.h"

/**
 * Setter/getter for the "from" field of an Link object.
 * @param from - it represents the user that created the link. It contains an id and name.
 */
void Link::setFrom(const IdNamePair &from)
{
	mFrom = from;
}
const IdNamePair &Link::getFrom() const
{
	return mFrom;
}

/**
 * Setter/getter for the "link" field of an Link object.
 * @param link - the URL that was shared
 */
void Link::setLink(const MAUtil::String &link)
{
	mLink = link;
}
const MAUtil::String &Link::getLink() const
{
	return mLink;
}

/**
 * Setter/getter for the "name" field of an Link object.
 * @param name - the name of the link
 */
void Link::setName(const MAUtil::String &name)
{
	mName = name;
}
const MAUtil::String &Link::getName() const
{
	return mName;
}

/**
 * Setter/getter for the "comments" field of an Link object.
 * @param comments - all of the comments on this link
 */
void Link::setComments(MAUtil::Vector<Comment> &comments)
{
	mComments.clear();
	mComments = comments;
}
const MAUtil::Vector<Comment> &Link::getComments() const
{
	return mComments;
}

/**
 * Setter/getter for the "description" field of an Link object.
 * @param descr - a description of the link (appears beneath the link caption).
 */
void Link::setDescription(const MAUtil::String &descr)
{
	mDescription = descr;
}
const MAUtil::String &Link::getDescription() const
{
	return mDescription;
}

/**
 * Setter/getter for the "picture" field of an Link object.
 * @param pictureUrl - a URL to the thumbnail image used in the link post.
 */
void Link::setPicture(const MAUtil::String &pictureUrl)
{
	mPicture = pictureUrl;
}
const MAUtil::String &Link::getPicture() const
{
	return mPicture;
}

/**
 * Setter/getter for the "message" field of an Link object.
 * @param message - the message from the user about this link.
 */
void Link::setMessage(const MAUtil::String &message)
{
	mMessage = message;
}
const MAUtil::String &Link::getMessage() const
{
	return mMessage;
}
