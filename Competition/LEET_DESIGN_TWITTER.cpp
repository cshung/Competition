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
        unordered_set<int> m_users;
        unordered_map<int, deque<pair<int, int>>> m_user_tweets;
        unordered_map<int, unordered_set<int>> m_following;
        unordered_map<int, unordered_set<int>> m_follower;
        unordered_map<int, deque<int>> m_news_feed_cache;
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
            if (this->m_users.find(userId) == this->m_users.end())
            {
                this->m_users.insert(userId);
                this->m_news_feed_cache.insert(make_pair(userId, deque<int>()));
            }

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

            auto selfCacheProbe = this->m_news_feed_cache.find(userId);
            if (selfCacheProbe != this->m_news_feed_cache.end())
            {
                if (selfCacheProbe->second.size() == MAX_TWEETS)
                {
                    selfCacheProbe->second.pop_back();
                }

                selfCacheProbe->second.push_front(tweetId);
            }

            auto followerSetProbe = this->m_follower.find(userId);
            if (followerSetProbe != this->m_follower.end())
            {
                for (auto fi = followerSetProbe->second.begin(); fi != followerSetProbe->second.end(); fi++)
                {
                    auto followerCacheProbe = this->m_news_feed_cache.find(*fi);
                    if (followerCacheProbe != this->m_news_feed_cache.end())
                    {
                        if (followerCacheProbe->second.size() == MAX_TWEETS)
                        {
                            followerCacheProbe->second.pop_back();
                        }

                        followerCacheProbe->second.push_front(tweetId);
                    }
                }
            }

            this->m_time++;
        }

        /** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
        vector<int> getNewsFeed(int userId)
        {
            vector<int> result;

            auto cacheProbe = this->m_news_feed_cache.find(userId);
            if (cacheProbe != this->m_news_feed_cache.end())
            {
                for (auto ci = cacheProbe->second.begin(); ci != cacheProbe->second.end(); ci++)
                {
                    result.push_back(*ci);
                }

                return result;
            }

            vector<pair<deque<pair<int, int>>::iterator, deque<pair<int, int>>::iterator>> following_tweets;
            deque<int> cache;
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

            while (result.size() < MAX_TWEETS)
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
                        else if (following_tweets[i].first->second > following_tweets[best].first->second)
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
                    cache.push_back(following_tweets[best].first->first);
                    following_tweets[best].first++;
                }
            }

            this->m_news_feed_cache.insert(make_pair(userId, cache));

            return result;
        }

        /** Follower follows a followee. If the operation is invalid, it should be a no-op. */
        void follow(int followerId, int followeeId)
        {
            if (this->m_users.find(followerId) == this->m_users.end())
            {
                this->m_users.insert(followerId);
                this->m_news_feed_cache.insert(make_pair(followerId, deque<int>()));
            }

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

            auto probeFollower = this->m_follower.find(followeeId);
            if (probeFollower == this->m_follower.end())
            {
                unordered_set<int> newFollower;
                newFollower.insert(followerId);
                this->m_follower.insert(pair<int, unordered_set<int>>(followeeId, newFollower));
            }
            else
            {
                probeFollower->second.insert(followerId);
            }

            // Invalidate my cache since I changed my following relationship
            if (this->m_news_feed_cache.find(followerId) != this->m_news_feed_cache.end())
            {
                this->m_news_feed_cache.erase(followerId);
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

            auto probeFollower = this->m_follower.find(followeeId);
            if (probeFollower != this->m_follower.end())
            {
                if (probeFollower->second.find(followerId) != probeFollower->second.end())
                {
                    probeFollower->second.erase(followerId);
                }
            }

            // Invalidate my cache since I changed my following relationship
            if (this->m_news_feed_cache.find(followerId) != this->m_news_feed_cache.end())
            {
                this->m_news_feed_cache.erase(followerId);
            }
        }
    };
};

using namespace _LEET_DESIGN_TWITTER;

int LEET_DESIGN_TWITTER()
{
    vector<int> result;
    Twitter twitter;
    twitter.postTweet(1, 5);
    result = twitter.getNewsFeed(1); for (size_t i = 0; i < result.size(); i++) { cout << result[i] << " "; } cout << endl;
    twitter.follow(1, 2);
    twitter.postTweet(2, 6);
    result = twitter.getNewsFeed(1); for (size_t i = 0; i < result.size(); i++) { cout << result[i] << " "; } cout << endl;
    twitter.unfollow(1, 2);
    result = twitter.getNewsFeed(1); for (size_t i = 0; i < result.size(); i++) { cout << result[i] << " "; } cout << endl;
    return 0;
}