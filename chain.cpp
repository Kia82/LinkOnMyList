

#include <math.h>
#include <iostream>
#include "chain.h"

/**
 * Constructs a Chain from an input image
 * Each Node will cover a nodedimension x nodedimension (in pixels)
 * region in the source image.
 * @param img the input image
 * @param nodedimension number of pixels along the width and height of the Block region
 * @pre input image's width and height are evenly divisible by nodedimension
**/
Chain::Chain(PNG& img, unsigned int nodedimension) {
	
	length_ = (img.width()  * img.height())/(nodedimension * nodedimension);

	if(length_ != 0 ) {
		NW =  new Node();
		SE = NW;
	for(unsigned int i = 0; i < length_; i++) {
		Node *temp = new Node();
		temp->next = NW;
		temp->next->prev = temp;
		NW = temp;
	}


	}


	Node* temp = NW;
	for(unsigned int i = 0; i < img.width(); i+= nodedimension) {
		for(unsigned int j = 0; j < img.height(); j += nodedimension) {
			Block b;
			temp->data.Build(img, i, j, nodedimension);	
			temp = temp->next;

		}
	}




}

/**
 * Renders the Chain's pixel data into an output PNG.
 * The PNG should be sized according to the number of nodes
 * specified by the cols parameter.
 * It is possible that there may not be enough nodes to fill
 * the bottom row of the PNG. If this happens, just render
 * as many nodes as there are, from left to right, and leave
 * the rest of the row as opaque white pixels.
 * @pre this Chain is not empty
 * @param cols the number of Blocks to use for the width of the image
 * @param full whether to render all pixel data into a full-size image,
 *             or block averages into a tiny image
**/
//KIA
PNG Chain::Render(unsigned int cols, bool full) {
	
	Node *temp = NW;
	unsigned int s = (temp->data).Dimension();
	int row_limit = 0;
	row_limit = (length_ + cols - 1) / cols;
		
	
PNG* imgFrame;
// row_limit = length_/cols + 1;
if (full){
	imgFrame = new PNG(s*cols,s*row_limit); 
} else {
	imgFrame = new PNG(cols,row_limit); 
}
	
	for(int row = 0; row < row_limit; row++) {
		for(int x = 0; x < cols; x++) {
		if(temp) {
			if(full) {
			temp->data.Render(*imgFrame, s*x,row*s,full);
			temp = temp->next;
			} else {
			temp->data.Render(*imgFrame, x,row,full);
			temp = temp->next;
			

			}
		}
			
	
		}
	}


// 	PNG Chain::Render(unsigned int cols, bool full) {
//     Node* temp = NW;
//     unsigned int s = (temp->data).Dimension();
//     int row_limit = (length_ + cols - 1) / cols;  // Calculate the number of rows needed

//     PNG* imgFrame = new PNG(s * cols, s * row_limit);

//     for (int row = 0; row < row_limit; row++) {
//         for (int x = 0; x < cols; x++) {
//             if (temp != nullptr) {
//                 if (full) {
//                     temp->data.Render(*imgFrame, s * x, row * s, full);
//                 } else {
//                     temp->data.Render(*imgFrame, x * s, row * s, full);
//                 }
//                 temp = temp->next;
//             } else {
//                 // If there are not enough nodes to fill the row, fill the remaining with white pixels
//                 for (int i = x; i < cols; i++) {
//                     for (int j = 0; j < s; j++) {
//                         for (int k = 0; k < s; k++) {
//                             imgFrame->GetPixel(x * s + j, row * s + k) = RGBAPixel(255, 255, 255);
//                         }
//                     }
//                 }
//                 break;  // Break the loop as there are no more nodes to process
//             }
//         }
//     }

//     return *imgFrame;
// }





	return *imgFrame;
	

	



	// cout << "!!!!!!!!!!!!!!!" << length_;

    // int dimension = NW->data.Dimension();
    // int rows;

    // if (this->Length() % cols == 0) {
    //     rows = this->Length() / cols;
    // } else {
    //     rows = this->Length() / cols + 1;
    // }

    // int count = 0;
    
    // if(full) {
    //     PNG * out = new PNG(cols * dimension, rows * dimension);
    //     Node * ptr = NW;
    //     for(int i = 0; i < rows; i++) {
    //         for(int j = 0; j < cols; j++) {
    //             if (count >= length_) 
    //             {
    //                 break;
    //             }
                
    //             ptr->data.Render(*out,j * dimension,i * dimension,full);
    //             ptr = ptr->next;
    //             count++;
    //         }
    //     }
    //     return *out;
        
    // }
    // else {
    //     PNG * out = new PNG(cols, rows);
    //     Node * ptr = NW->next;
    //     for(int i = 0; i < rows; i++) {
    //         for(int j = 0; j < cols; j++) {
    //             if (count >= length_) 
    //             {
    //                 break;
    //             }
    //             ptr->data.Render(*out,j,i,full);
    //             ptr = ptr->next;
    //             count++;
    //         }
    //     }
    //     return *out;
    // }
 }



/**
 * Inserts a new Node containing ndata at the back of the Chain
**/
//KIA
void Chain::InsertBack(const Block& ndata) {

	Node* newNode = new Node(ndata);
	SE->next = newNode;
	SE->next->prev = SE;
	length_ += 1;

    
}

/**
 * Reverses the structure of the list. This must be done by
 * pointer assignments. You may not deallocate or allocate any Nodes.
 * Example:
 *	before:	NW -> A <-> B <-> C <-> D <-> E <-> F <-> G <-> H <- SE
 *  
 *  after:	NW -> H <-> G <-> F <-> E <-> D <-> C <-> B <-> A <- SE
**/
//ALI
// void Chain::Reverse() {
// 	// complete your implementation below
// 	//BRYAN
// 	Node * curr = NW;
//     while (curr != SE)
//     {
//         Node * prev = curr->prev;
//         curr->prev = curr->next;
//         curr->next = prev;
//         curr = curr->prev;
//     }
    
//     Node * old = SE;
//     SE = NW;
//     NW = old;
//     NW->next = NW->prev;
//     SE->prev = SE->next;
	// Node* head = NW;
	// Node* head2 = NW;
	// Node* ptr2 = head->next;
	// head ->next = NULL;
	// head ->prev = ptr2;
	// while (ptr2) {
	// 	ptr2->prev = ptr2->next;
	// 	ptr2->next = head;
	// 	ptr2 = ptr2->prev;
	// }
	// NW = head;
	// while (head->next) {
	// 	head = head->next;
	// }
	// SE = head;
	// //SE = head2;
    // Node* temp = NW;
	// NW = SE;
	// SE = temp;
//}

void Chain::Reverse() {
    if (NW == nullptr || SE == nullptr || NW == SE) {
        // Empty list or a single-node list, nothing to reverse
        return;
    }

    Node *curr = NW;
    Node *prev = nullptr;
    Node *next = nullptr;

    while (curr != nullptr) {
        next = curr->next;
        curr->next = prev;
        curr->prev = next;
        prev = curr;
        curr = next;
    }

    // Update head and tail pointers
    Node *oldTail = SE;
    SE = NW;
    NW = oldTail;
    NW->next = nullptr;   // Set the next of the new head to null
    SE->prev = nullptr;   // Set the prev of the new tail to null
}


/**
 * Rearranges the Node structure and internal pixel data to be flipped over a vertical axis.
 * This must be done using pointer assignments.
 * You may not deallocate or allocate any Nodes.
 * Example, length = 6:
 *  before, flipping with 3 columns (2 rows):
 *
 *		NW -> A> <-> B> <-> C> <->
 *            D> <-> E> <-> F> <- SE
 * 
 *  after, visualized with 3 columns (2 rows):
 * 
 *		NW -> <C <-> <B <-> <A <->
 *            <F <-> <E <-> <D <- SE
 * 
 * @param cols number of Blocks to use for the initial width of the image
 * @pre length_ is divisible by cols (i.e. no "partially-filled" rows)
**/
//ALI
void Chain::FlipHorizontal(unsigned int cols) {
	// complete your implementation below
	Node* temp = NW;
	for (int j = 0; j < (length_ / cols); j++) {
		for (int i = 0; i < cols; i++) {
		temp->data.FlipHorizontal();
		temp = temp->next;
		}
		Node* end = temp->prev;
		end->next = NULL;
		Reverse();
		end->next = temp;
	}

}

/**
 * Rearranges the Node structure and internal pixel data to be flipped over a horizontal axis.
 * This must be done using pointer assignments.
 * You may not deallocate or allocate any Nodes.
 * Example, length = 6:
 *	before, flipping with 3 columns (2 rows):
 *                         
 *      NW -> A <-> B <-> C <->
 *            D <-> E <-> F <- SE
 * 
 *  after, visualized with 3 columns (2 rows):
 * 
 *      NW -> D <-> E <-> F <->
 *            A <-> B <-> C <- SE
 * 
 * @param cols number of Blocks to use for the initial width of the image
 * @pre length_ is divisible by cols (i.e. no "partially-filled" rows)
**/
//ALI
void Chain::FlipVertical(unsigned int cols) {
Node* temp = NW;
Node* temp2 = SE;
bool cont = true;

while (cont) {
    Node* tempNext = temp->next;
    Node* tempPrev = temp->prev;
    Node* temp2Next = temp2->next;
    Node* temp2Prev = temp2->prev;

    // Swap pointers for temp and temp2
    temp->next = temp2Next;
    temp->prev = temp2Prev;
    temp2->next = tempNext;
    temp2->prev = tempPrev;

    // Move pointers forward
    temp = tempNext;
    temp2 = temp2Prev;

    // Move temp2 to the next block
    for (unsigned int i = 1; i < cols; i++) {
        if (temp2 != nullptr) {
            temp2 = temp2->prev;
        } else {
            break;  // Break if reaching the end of the list
        }
    }

    // Move temp to the next block
    Node* temp4 = temp2;
    for (unsigned int i = 0; i < cols; i++) {
        if (temp != nullptr) {
            temp = temp->next;
        } else {
            break;  // Break if reaching the end of the list
        }
    }

    // Check termination conditions
    if (temp4 == nullptr || temp2 == nullptr || temp4 == temp || temp2 == temp) {
        cont = false;
    }
}

}

/**
 * Produces a blocky, pixellated effect (in a rendered image) by replacing each
 * block's pixel data with the average color of the block.
**/
//KIA
void Chain::Blockify() {
	Node* temp = NW;
	while(temp != NULL) {
		temp->data.FillAverage();
		temp = temp->next;
	}



}

/**
 * Destroys all dynamically allocated memory associated with
 * this Chain object. Called by destructor and operator=.
 * You must complete its implementation for PA1.
**/
//KIA
void Chain::Clear() {

	Node *temp = NW;

	while(NW != NULL) {
		temp = temp->next;
		delete NW;
		NW = temp;
	}
	NW = NULL;
	SE = NULL;
    
}

/**
 * Copies the parameter other Chain into the current Chain.
 * Does not free any memory. Called by copy constructor and
 * operator=.
 * You must complete its implementation for PA1.
 * @param other The Chain to be copied.
**/
//
void Chain::Copy(const Chain& other) {
	// complete your implementation below
    length_ = other.length_;
	Node* temp = NW;
	while (temp->next){
		Node* temp2 = temp->next;
		delete temp;
		temp = temp2;
	}
	NW->data = other.NW->data;
	NW->next = other.NW->next;
	NW->prev = other.NW->prev;
	temp = other.NW->next;
	while (temp->next) {
		InsertBack(temp->data);
		temp = temp->next;
	}

}

/**
 * If you have declared any private helper functions in chain_private.h,
 * add your completed implementations below.
**/

