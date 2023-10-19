
#include "Game.hpp"
#include "AdminPlayer.hpp"
Game::Game(){
    numP=0;
    dice.setSize(5);
    //AdminPlayer playerAdmin;
    //playerAdmin.showUsers();
}

void Game::start(){
    srand((unsigned int)time(0));
    
    int temp;
    string name;
    
    //Get users to sign-in
    //User/Admin is needed. Just create an admin class that is friends with
    //player. This way we can pull the information we want and utilize the existing
    //code for reading/writing. Admin will have access to ALL Player member
    //variables AND functions (private, public, protected). This will give the
    //admin FULL privilege rights.
    //We will need to add a function to log-in, this will create a separate file
    //that will store user name (SHA1 hash) and password (SHA256 hash) and user
    //privilege (admin/standard). We will have options for players to add more players
    //or to play the game (1-4 players). 
    
    //Check if etc/passwd.bin exist
    checkFile();
    int choice;
    bool again=true;
    do{
        choice=loginMenu();
        switch(choice){
            case 1:system("clear");addPlayer();break;//Add user (login)
            case 2:system("clear");createPlayer();break;//Create new user
            case 3:
                system("clear");
                if(players.size()<1){
                    cout<<setw(21)<<""<<"No Players in Queue..."<<endl;
                    break;
                }
                else{
                    play();//Play game -> play()
                    again=playAgain();
                    //Clear the vector
                    players.clear();
                    break;
                }
        }
        system("clear");
    }while((choice!=4) && (again));
}

void Game::play(){
    //Calculate Score Cards/Winners
    string winner;
    int highScore=0;    
    
    //Multiplayer
    if(numP>1){
        bool endGame=gameOver();
        int currentPlayerIndex = 0;
        
        while(!endGame){
            players[currentPlayerIndex].takeTurn(dice);
            if(!players[currentPlayerIndex].isPlayerDone())
                printCard(players[currentPlayerIndex]);
            pause();
            currentPlayerIndex = (currentPlayerIndex + 1) % numP;
            endGame=gameOver();
        }
        
        for(int i=0;i<numP ;i++){
            Player currPlayer = players[i];
            currPlayer.setScore();
            currPlayer.saveCard();
            int score = currPlayer.getScore();
            if (score > highScore) {
                winner = currPlayer.getName();
                highScore = score;
            }
            currPlayer.printCard();
        }
        cout<<setw(21)<<""<<"Game winner: "<<winner<<endl;
        cout<<setw(21)<<""<<"Total Score: "<<highScore<<endl;
    }
    //Single Player
    else{
        Player currPlayer = players[0];
        while(!currPlayer.isPlayerDone()){
            currPlayer.takeTurn(dice);
            if(!currPlayer.isPlayerDone())printCard(currPlayer);
            pause();
        }
        currPlayer.setScore();
        currPlayer.saveCard();
        highScore = currPlayer.getScore();
        cout<<setw(21)<<""<<"Total Score: "<<highScore<<endl;
        currPlayer.printCard();
    }
}
void Game::printCard(Player currPlayer){
    cout<<setw(21)<<""<<currPlayer.getName()<<", "<<endl;
    cout<<setw(21)<<""<<"Would you like to view your score card?"<<endl;
    cout<<setw(21)<<""<<"Enter Yes/No: ";
    string ans;
    cin>>ans;
    ans = ScoreCard::format(ans);
    if(ans!="Yes" && ans!="No"){
        cin>>ans;
    }
    if(ans=="Yes"){
        currPlayer.printCard();
    }
    cin.ignore(1000,'\n');
}
void Game::pause(){
    char key;
    cout<<setw(21)<<""<<"Press ENTER to continue...   ";
    cin.get();
}
void Game::end(){
    menu.printExit();
}
bool Game::gameMenu(bool &debugGame){
    int dec;
    
    menu.printMainMenu();
    cout<<setw(32)<<"Selection: ";
    cin>>dec;
    if(dec==8675309){debugGame=true;return false;}
    //Check if decision is within range
    while(dec>3 || dec<1){
        cout<<setw(21)<<""<<"INVALID SELECTION:"<<endl;
        cout<<setw(21)<<""<<"Try Again: ";
        cin>>dec;
    }
    //Print Rules
    if(dec==2){
        menu.printRules();
        cout<<endl<<endl<<endl;
        return gameMenu(debugGame);
    }
    //Play the game
    else if(dec==1) return true;
    return false;
}
bool Game::playAgain(){
    cout<<setw(21)<<""<<"Would you like to play another game?(Yes/No)"<<endl;
    string ans;
    cout<<setw(21)<<"";
    getline(cin,ans);
    ans=ScoreCard::format(ans);
    players.clear();
    if(ans=="Yes") return true;
    return false;
}
bool Game::gameOver(){
    bool gameOver=true;
    for(int i=0;i<numP;i++) {
        if(!players[i].isPlayerDone()) {
            gameOver = false;
            break;
        }
    }
    return gameOver;
}
int Game::loginMenu(){
    int choice;
    
    do{
        menu.printLogin();
        cout<<setw(32)<<"Selection: ";
        cin>>choice;
        cin.ignore(1000,'\n');
    }
    while(choice>3 && choice<1);
    
    return choice;
}
void Game::addPlayer(){
    if(numP<=4){
        fstream file;
        file.open("etc/passwd.bin",ios::in|ios::binary);
        long cursor=0L;
        Scanner sc;
        //Give a login screen that will ask for the username/password
        cout<<setw(21)<<""<<"Enter username: ";
        char* uname=sc.nextChar();
        //Search for username
        if(usernameCheck(file,uname)){
            cout<<setw(21)<<""<<"Enter password: ";
            char* password=sc.nextChar();
            if(!validPassword(file,password)){
                cout<<setw(21)<<""<<"Invalid Password"<<endl;
            }
            else{
                //Check privilege level
                Privilege priv=getPrivilege(file);
                if(priv==Privilege::Admin){
                    //Admin menu
                    AdminPlayer admin;
                    admin.adminSession(menu);
                }
                else{
                    //Get the user ID
                    unsigned int id=getID(file);
                    //Add the player into the queue
                    Player player(uname,id);
                    players.push_back(player);
                    //Randomize players
                    if(players.size()>1){
                        int index1=rand()%players.size();
                        int index2=rand()%players.size();
                        while(index1==index2){
                            index2=rand()%players.size();
                        }
                        //Swap players
                        Player temp=players[index1];
                        players[index1]=players[index2];
                        players[index2]=temp;
                    }
                }
            }
            delete[] password;
        }
        else{
            cout<<setw(21)<<" "<<"No User Name on Record"<<endl;
        }
        file.close();
        delete[] uname;
        numP=players.size();
    }
    else{
        cout<<setw(21)<<" "<<"Maximum number of players reached"<<endl;
    }
}
void Game::createPlayer(){
    //Get username/password, set priv to standard, get userID from last
    //userId from file - increment to set ID
    Player player;
    Scanner sc;
    fstream file;
    file.open("etc/passwd.bin",ios::in|ios::binary);

    cout<<setw(21)<<""<<"Enter username: ";
    char* userName=sc.nextChar();
    //Make sure username doesnt already exists
    if(!usernameCheck(file,userName)){
        cout<<setw(21)<<""<<"Enter password: ";
        char* password=sc.nextChar();
        //Validate password
        while(!passwordFormat(password)){
            delete[] password;
            password=sc.nextChar();
        }
        //Hash username/password
        SHA1 nameHash(userName);
        SHA256 passHash(password);
        char* nameDigest=(char*)nameHash.getDigest();
        char* passDigest=(char*)passHash.getDigest();

        //Set privilege
        Privilege priv=Privilege::Standard;
        //Set user ID
        unsigned int id=setID();
        //Save to passwd.bin file
        fstream file;
        file.open("etc/passwd.bin",ios::out|ios::binary|ios::app);
        file.seekp(0,ios::end);
        file.write(nameDigest,sizeof(char)*20);
        file.write(passDigest,sizeof(char)*32);
        file.write(reinterpret_cast<char*>(&priv),sizeof(int));
        file.write(reinterpret_cast<char*>(&id),sizeof(unsigned int));
        file.close();
        playerRecords(userName,id);
        fstream pFile;
        string name=userName;
        string userID=to_string(id);
        string fileName="saves/" + name + "_" + userID +".sav";
        pFile.open(fileName,ios::out|ios::binary);
        //Clean up memory
        delete[] password;
    }
    else{
        cout<<"Username already exist..."<<endl;
    }
    //Clean up memory
    file.close();
    delete[] userName;
}
bool Game::usernameCheck(fstream& file,char* userName){
    //Search through the file to see if the userName exists, if it does return true
    //else return false
    SHA1 hash(userName);
    char* digest=(char*)hash.getDigest();
    long cur=file.tellg();
    long cursor=0L;
    file.seekg(0,std::ios::end);
    int size=file.tellg();
    char tmp[20];
    int userNameBlock=0;
    while(cursor<size){
        //Iterate through the file, grab each userName hash and compare
        file.seekg(cursor,std::ios::beg);
        file.read(tmp,sizeof(char)*20);
        
        if(memcmp(digest,tmp,sizeof(char)*20)==0){
            return true;
        }
        else{
            cursor+=((sizeof(char)*20)+(sizeof(char)*32)+sizeof(int)+sizeof(unsigned int));
        }
    }
    //delete[] tmp;
    file.clear();
    file.seekg(cur,std::ios::beg);
    //Since the userName doesnt exist, we can place the file pointer back to read
    //the previous user ID, this will allow us to increment the uID

    return false;

}
bool Game::passwordFormat(char* passwd){
    //Password needs capital letter, lower case letter, number, length and
    //special character (! @ # $ &)
    //Use some sort of bit manip to check if all categories are set
    // x x x | _ _ _ _ _ -> last 5 bits will represent out conditions
    char passSet=0;
    int len = strlen(passwd);
    if(len>=8){
        passSet|=16;
    }
    for(int i=0;i<len;i++){
        if(isupper(passwd[i]))
            passSet|=8;
        if(islower(passwd[i]))
            passSet|=4;
        if(isdigit(passwd[i]))
            passSet|=2;
        if((passwd[i]=='!') || (passwd[i]=='@')
            || (passwd[i]=='#') || (passwd[i]=='$')
                || (passwd[i]=='&'))
            passSet|=1;
    }
    if(passSet!=31){
        std::cout<<"Password criteria not met"<<std::endl;
        std::cout<<"Need:\n\tAt least 8 characters\n\tCapital Letter\n\tLower Case Letter"
                "\n\tNumber\n\tSpecial Character(! @ # $ &)"<<std::endl;
        return false;
    }
    return true;
}
bool Game::validPassword(fstream& file,char* password){
    SHA256 hash(password);
    char* digest=(char*)hash.getDigest();
    char fileDigest[32];
    
    file.seekg(0,ios::cur);
    file.read(fileDigest,sizeof(char)*32);
    if(memcmp(fileDigest,digest,sizeof(char)*32)==0){
        return true;
    }
    return false;
}
Privilege Game::getPrivilege(fstream& file){
    Privilege priv;
    file.seekg(0,ios::cur);
    file.read(reinterpret_cast<char*>(&priv),sizeof(int));
    return priv;
}
unsigned int Game::setID(){
    fstream file;
    unsigned int id;
    file.open("etc/passwd.bin",ios::in|ios::binary);
    //We know the last user id is stored in the last 32 bit chunk of the user block
    //So we can open the file -32 bits from the end of the file
    long cursor=-(sizeof(unsigned int));
    file.seekp(cursor,ios::end);
    file.read(reinterpret_cast<char*>(&id),sizeof(unsigned int));
    file.close();
    id++;
    return id;
}
unsigned int Game::getID(fstream& file){
    unsigned int id;
    file.seekg(0,ios::cur);
    file.read(reinterpret_cast<char*>(&id),sizeof(unsigned int));
    return id;
}
void Game::debugGame(){
    //Create a fake player
    Player player("Debug",0);
    numP=1;
    players[0]=player;
    Player currPlayer=players[0];

    while(!currPlayer.isPlayerDone()){
        //Change player score card
        currPlayer.debugPlayer(dice);
    }
    currPlayer.setScore();
    int score=currPlayer.getScore();
    currPlayer.printCard();
    cout<<"currPlayer="<<currPlayer.getName()<<endl;
    cout<<"score="<<score<<endl;
    currPlayer.saveCard();
}
void Game::checkFile(){
    fstream file;
    string fileName="etc/passwd.bin";
    file.open(fileName,ios::in|ios::binary);
    if(!file.is_open()){
        createFile(fileName);
    }
    else{
        file.close();
    }
    fileName="home/user_info.dat";
    file.open(fileName,ios::in|ios::binary);
    if(!file.is_open()){
        createFile(fileName);
    }
    else{
        file.close();
    }
}
void Game::createFile(string fileName){
    fstream file;
    file.open(fileName,ios::out|ios::binary);
    
    if(fileName.compare("etc/passwd.bin")==0){
        //Create admin user
        char name[] = "admin";
        char password[] = "password";
        Privilege priv=Privilege::Admin;
        unsigned int userID=0;
        //Hash username
        SHA1 nameHash(name);
        char* nameDigest=(char*)nameHash.getDigest();
        //Hash password
        SHA256 passwdHash(password);
        char* passwdDigest=(char*)passwdHash.getDigest();

        file.seekp(0,ios::beg);
        file.write(nameDigest,sizeof(char)*20);
        file.write(passwdDigest,sizeof(char)*32);
        file.write(reinterpret_cast<char*>(&priv),sizeof(int));
        file.write(reinterpret_cast<char*>(&userID),sizeof(unsigned int));
    }
    
    file.close();
}

void Game::playerRecords(char* uname,unsigned int id){
    fstream file("home/user_info.dat",ios::out|ios::binary|ios::app);
    
    int size = strlen(uname)+1;//Add 1 to get the null terminator
    //Load Id first, this will make searching a little faster
    file.write(reinterpret_cast<const char*>(&id), sizeof(unsigned int));
    file.write(reinterpret_cast<const char*>(&size), sizeof(int));
    file.write(uname,size);//Keep var length data at end
    //Close file
    file.close();
}