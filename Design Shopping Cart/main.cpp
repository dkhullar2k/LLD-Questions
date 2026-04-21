#include "Product.cpp"
#include "User.cpp"
#include "CartService.cpp"
#include "Discount.cpp"

int main(){

    CartService cartService;

    Product p1("product_123","Monitor",320);
    Product p2("product_456","Mobile",500);

    User u1("uid_123","Dhruv");
    
    cartService.addItem(u1,p1,2);
    cartService.addItem(u1,p2,3);
    cartService.viewCart(u1);
    cartService.checkout(u1);

    cartService.updateItem(u1,p2,1);
    cartService.viewCart(u1);
    cartService.checkout(u1);

    DiscountStrategy* discount=new PercentageDiscount(20);
    cartService.applyDiscount(u1,discount);
    cartService.checkout(u1);

    cartService.deleteItem(u1,p1);
    cartService.viewCart(u1);
    cartService.checkout(u1);

    cartService.deleteItem(u1,p1);
    delete discount;
}