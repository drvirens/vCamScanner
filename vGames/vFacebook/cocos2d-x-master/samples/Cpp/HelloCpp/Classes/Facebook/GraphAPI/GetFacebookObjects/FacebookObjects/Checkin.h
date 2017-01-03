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

/**
 * @file Checkin.h
 * @author Gabriela Rata
 */

#ifndef CHECKIN_H_
#define CHECKIN_H_

#include "FacebookObject.h"
#include "Utilities.h"
#include "Comment.h"

/**
 * \brief Implements an Checkin Facebook object.
 * See: http://developers.facebook.com/docs/reference/api/checkin/
 */
class Checkin: public FacebookObject
{
public:

	/**
	 * Setter/getter for the "from" field of an Checkin object.
	 * @param from - it represents the person/application that created the checkin. It contains the id and the name.
	 */
	void setFrom(const IdNamePair &from);
	const IdNamePair &getFrom() const;

	/**
	 * Setter/getter for the "tags" field of an Checkin object.
	 * @param name - the users the author tagged in the checkin
	 */
	void setTags(const MAUtil::Vector<IdNamePair> &tags);
	const MAUtil::Vector<IdNamePair> &getTags() const;

	/**
	 * Setter/getter for the "place" field of an Checkin object.
	 * @param place - information about the Facebook Page that represents the location of the checkin
	 */
	void setPlace(const Place &place);
	const Place &getPlace() const;

	/**
	 * Setter/getter for the "likes" field of an Checkin object.
	 * @param likes - users who like the checkin
	 */
	void setLikes(const MAUtil::Vector<IdNamePair> &likes);
	const MAUtil::Vector<IdNamePair> &getLikes() const;

	/**
	 * Setter/getter for the "message" field of an Checkin object.
	 * @param message - the message the user added to the checkin
	 */
	void setMessage(const MAUtil::String &message);
	const MAUtil::String &getMessage() const;

	/**
	 * Setter/getter for the "comments" field of an Checkin object.
	 * @param comments - the message the user added to the checkin
	 */
	void setComments(const MAUtil::Vector<Comment> &comments);
	const MAUtil::Vector<Comment> &getComments() const;

	/**
	 * Setter/getter for the "app" field of an Checkin object.
	 * @param app - information about the application that made the checkin
	 */
	void setApplication(const IdNamePair &app);
	const IdNamePair &getApplication() const;

private:
	IdNamePair					mFrom;
	MAUtil::Vector<IdNamePair> 	mTags;
	Place						mPlace;
	MAUtil::Vector<IdNamePair> 	mLikes;
	MAUtil::String				mMessage;
	MAUtil::Vector<Comment>		mComments;
	IdNamePair					mApplication;
};

#endif /* CHECKIN_H_ */
