/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* deleteDuplicates(struct ListNode* head) {
    struct ListNode* cur = head; // Pointer to traverse the list
    
    while (cur != NULL && cur->next != NULL) {
        if (cur->val == cur->next->val) { // Duplicate found
            struct ListNode* dup = cur->next; // Node to be deleted
            cur->next = cur->next->next; // Bypass the duplicate node
            free(dup);
        } else {
            cur = cur->next; // Move to the next node
        }
    }
    
    return head; // Return new head of the list
}
