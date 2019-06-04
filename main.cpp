#include <iostream>
#include "gtest/gtest.h"
#include <vector>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}

};
class Solution {
public:
    static ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {

        int n1=0,  maradek=0;
        n1=l1->val+l2->val+maradek;
        maradek=n1/10;
        n1-=maradek*10;
        ListNode *resultt=new ListNode(n1);
        ListNode *temp=resultt;
        l1=l1->next;
        l2=l2->next;
        while (l1!=nullptr && l2!=nullptr)
        {
            n1=l1->val+l2->val+maradek;
            maradek=n1/10;
            n1-=maradek*10;
            l1=l1->next;
            l2=l2->next;
            ListNode *node=new ListNode(n1);
            resultt->next=node;
            resultt=node;

        }
        while(l1!=nullptr || l2!=nullptr){
            n1=0;
            if(l1!=nullptr){
                n1+=l1->val;
                l1=l1->next;
            }
            if(l2!=nullptr){
                n1+=l2->val;
                l2=l2->next;
            }
            n1+=maradek;
            maradek=n1/10;
            n1-=maradek*10;
            ListNode *node=new ListNode(n1);
            resultt->next=node;
            resultt=node;

        }
        if (maradek !=0)
        {
            ListNode *node=new ListNode(maradek);
            resultt->next=node;
            resultt=node;
        }

        return temp;
    }

};


bool step_to_next_node(ListNode* &list)
{
    if (list != nullptr)
    {
        list=(list)->next;
        return true;
    }
        return false;
}

bool are_lists_equal(ListNode* first, ListNode* second)
{

    while(!((first == nullptr) && (second == nullptr)))
    {
        if (first==nullptr || second==nullptr || first->val != second->val)
        {
            return false;
        }
        if (!(step_to_next_node(first)==true && step_to_next_node(second)==true))
        {
            return false;
        }

    }
    return true;

}

ListNode* build_linked_list(std::vector<int> input_array)
{
    ListNode *head=new ListNode(input_array[0]);
    ListNode *temp=head;

    for (unsigned long int i=1;i<input_array.size();++i) {
        ListNode *n=new ListNode(input_array[i]);
        temp->next=n;
        temp=n;
    }

    return head;
}

void clean_up_test_case(ListNode* list)
{
    ListNode* follower=list;

    while(list!=nullptr)
    {
        list=(follower->next);
        delete follower;
        follower=list;
    }
}

void clean_up_test(std::vector<ListNode*> &resources)
{
    for (unsigned int i=0;i<resources.size();++i)
    {
        clean_up_test_case(resources[i]);
    }
}

std::vector<ListNode*> build_resources( std::vector<int> one, std::vector<int> two,std::vector<int> exp_result_array)
{
    ListNode *first=(build_linked_list(one));

    ListNode *second=(build_linked_list(two));
    ListNode *expected_result=(build_linked_list(exp_result_array));
    ListNode *result=(Solution::addTwoNumbers(first,second));
    std::vector<ListNode*> resources={first, second, expected_result, result};
    return resources;
}

TEST(add_two_numbers, First) {
    std::vector<int> one={9,1};
    std::vector<int> two={1,8,1,1};
    std::vector<int> exp_result_array={0,0,2,1};
    std::vector<ListNode*> resources=build_resources(one,two,exp_result_array);
    EXPECT_TRUE(are_lists_equal(resources[2],resources[3]));
    clean_up_test(resources);


}

TEST(add_two_numbers, Second) {
    std::vector<int> one={1};
    std::vector<int> two={2};
    std::vector<int> exp_result_array={3};
    std::vector<ListNode*> resources=build_resources(one,two,exp_result_array);
    EXPECT_TRUE(are_lists_equal(resources[2],resources[3]));
    clean_up_test(resources);


}
TEST(add_two_numbers, Third) {
    std::vector<int> one={1,1,1,1,1,1,1,1,1};
    std::vector<int> two={2};
    std::vector<int> exp_result_array={3,1,1,1,1,1,1,1,1};
    std::vector<ListNode*> resources=build_resources(one,two,exp_result_array);
    EXPECT_TRUE(are_lists_equal(resources[2],resources[3]));
    clean_up_test(resources);


}
TEST(add_two_numbers, Fourth) {
    std::vector<int> one={5,9,5,5,5};
    std::vector<int> two={5,0,4,4,4};
    std::vector<int> exp_result_array={0,0,0,0,0,1};
    std::vector<ListNode*> resources=build_resources(one,two,exp_result_array);
    EXPECT_TRUE(are_lists_equal(resources[2],resources[3]));
    clean_up_test(resources);


}
int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
