#include "handlers.hpp"
#include "my_server.hpp"
using namespace std;

int main(int argc, char **argv) {
  try 
  {
  	Manager * manager = new Manager();
    MyServer server(argc > 1 ? atoi(argv[1]) : 5000);
    server.setNotFoundErrPage("static/404.html");
    server.get("/openlogin", new ShowPage("static/login.html"));
    server.get("/opensignup", new ShowPage("static/signup.html"));
    server.get("/login", new ShowPage("static/login.html"));
    server.get("/signup", new ShowPage("static/signup.html"));
    server.get("/uot.gif", new ShowImage("static/uot.gif"));
    server.get("/index.png", new ShowImage("static/index.png"));
    server.get("/", new ShowPage("static/home.html"));
    server.get("/bg.jpg", new ShowImage("static/bg.jpg"));
    server.get("/login_wrong", new ShowPage("static/login_wrong.html"));
    server.get("/signup_existed", new ShowPage("static/signup_existed.html"));
    server.get("/publisher", new ShowPage("static/publisher.html"));
    server.get("/add", new ShowPage("static/post_film.html"));
    server.get("/customer", new ShowPage("static/customer.html"));
    server.get("/send_to_add_money", new ShowPage("static/add_money.html"));
    server.post("/signup", new SignupHandler(manager));
    server.post("/login_wrong", new LoginHandler(manager));
    server.post("/signup_existed", new SignupHandler(manager));
    server.post("/add_a_film", new PostfilmHandler(manager));
    server.post("/see_published", new SeepublishedHandler(manager));
    server.post("/see_bought", new SeeboughtHandler(manager));
    server.post("/login", new LoginHandler(manager));
    server.post("/send_money", new SendmoneyHandler(manager));
    server.post("/delete_film", new DeletefilmHandler(manager));
    server.post("/buy", new BuypageHandler(manager));
    server.post("/buy_film", new BuyfilmHandler(manager));
    server.post("/see_films", new SeefilmsHandler(manager));
    server.post("/see_detail", new SeedetailHandler(manager));
    server.post("/logout", new LogoutHandler(manager));
    server.post("/rate", new RateHandler(manager));
    server.post("/filter", new FilterHandler(manager));
    server.post("/comment", new CommentHandler(manager));
    server.run();
  } catch (Server::Exception e) {
    cerr << e.getMessage() << endl;
  }
}
