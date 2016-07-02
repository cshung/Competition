#include "stdafx.h"

// https://leetcode.com/problems/design-twitter/

#include "LEET_DESIGN_TWITTER.h"
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <deque>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_DESIGN_TWITTER
{
    const int MAX_TWEETS = 10;

    class Twitter {
    private:
        unordered_map<int, deque<pair<int, int>>> m_user_tweets;
        unordered_map<int, unordered_set<int>> m_following;
        int m_time;
    public:
        /** Initialize your data structure here. */
        Twitter()
        {
            this->m_time = 0;
        }

        /** Compose a new tweet. */
        void postTweet(int userId, int tweetId)
        {
            auto probe = this->m_user_tweets.find(userId);
            if (probe == this->m_user_tweets.end())
            {
                deque<pair<int, int>> new_user_tweets;
                new_user_tweets.push_front(pair<int, int>(tweetId, this->m_time));
                this->m_user_tweets.insert(pair<int, deque<pair<int, int>>>(userId, new_user_tweets));
            }
            else
            {
                deque<pair<int, int>>& old_user_tweets = probe->second;
                if (old_user_tweets.size() == MAX_TWEETS)
                {
                    old_user_tweets.pop_back();
                }
                old_user_tweets.push_front(pair<int, int>(tweetId, this->m_time));
            }

            this->m_time++;
        }

        /** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
        vector<int> getNewsFeed(int userId)
        {
            vector<pair<deque<pair<int, int>>::iterator, deque<pair<int, int>>::iterator>> following_tweets;
            auto selfProbe = this->m_user_tweets.find(userId);
            if (selfProbe != this->m_user_tweets.end())
            {
                following_tweets.push_back(make_pair(selfProbe->second.begin(), selfProbe->second.end()));
            }

            auto followingSetProbe = this->m_following.find(userId);
            if (followingSetProbe != this->m_following.end())
            {
                for (auto fi = followingSetProbe->second.begin(); fi != followingSetProbe->second.end(); fi++)
                {
                    auto followingProbe = this->m_user_tweets.find(*fi);
                    if (followingProbe != this->m_user_tweets.end())
                    {
                        following_tweets.push_back(make_pair(followingProbe->second.begin(), followingProbe->second.end()));
                    }
                }
            }

            vector<int> result;

            while (result.size() < 10)
            {
                size_t best = -1;
                for (size_t i = 0; i < following_tweets.size(); i++)
                {
                    if (following_tweets[i].first != following_tweets[i].second)
                    {
                        // We have an item in a following tweet
                        if (best == -1)
                        {
                            best = i;
                        }
                        else if (following_tweets[i].first->second < following_tweets[best].first->second)
                        {
                            best = i;
                        }
                    }
                }
                if (best == -1)
                {
                    break;
                }
                else
                {
                    result.push_back(following_tweets[best].first->first);
                    following_tweets[best].first++;
                }
            }

            return result;
        }

        /** Follower follows a followee. If the operation is invalid, it should be a no-op. */
        void follow(int followerId, int followeeId)
        {
            if (followerId == followeeId)
            {
                // Never follow myself
                return;
            }

            auto probeFollowing = this->m_following.find(followerId);
            if (probeFollowing == this->m_following.end())
            {
                unordered_set<int> newFollowing;
                newFollowing.insert(followeeId);
                this->m_following.insert(pair<int, unordered_set<int>>(followerId, newFollowing));
            }
            else
            {
                probeFollowing->second.insert(followeeId);
            }
        }

        /** Follower unfollows a followee. If the operation is invalid, it should be a no-op. */
        void unfollow(int followerId, int followeeId)
        {
            auto probeFollowing = this->m_following.find(followerId);
            if (probeFollowing != this->m_following.end())
            {
                if (probeFollowing->second.find(followeeId) != probeFollowing->second.end())
                {
                    probeFollowing->second.erase(followeeId);
                }
            }
        }
    };
};

using namespace _LEET_DESIGN_TWITTER;

int LEET_DESIGN_TWITTER()
{
    Twitter twitter;
    twitter.postTweet(1, 3);
    twitter.postTweet(1, 5);
    vector<int> result = twitter.getNewsFeed(1);
    for (size_t i = 0; i < result.size(); i++)
    {
        cout << result[i] << endl;
    }
    return 0;
}