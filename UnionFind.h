//
// Created by Adi on 24/12/2022.
//

#ifndef TEA_CPP_UNIONFIND_H
#define TEA_CPP_UNIONFIND_H

#include "Array.h"
#include "NodeUF.h"


template<typename T>
class UnionFind {
public:
    Array<NodeUF<T>*> tablePlayers;
    explicit UnionFind();
    NodeUF<T>* Makeset(T* player, Team* teamPtr);


    Team* teamPurchase(Team* BuyingTeam,Team* BoughtTeam);

    void AddPlayerToTeam(T* player, Team* team);

    T* Find(int playerId);
//    bool exists(int playerId);

//    bool teamDead(int playerId);

//    permutation_t SumSpirit(T* player);

    int SumGames(T* player);
    void removeAllPlayers();

};

template<typename T>
NodeUF<T>* UnionFind<T>::Makeset(T* player, Team* teamPtr) {
    NodeUF<T>* tmp = tablePlayers.insert(player);
    teamPtr->set_head_player(tmp);
    tmp->_size = 1;
    tmp->_team = teamPtr;
    return tmp;
}

template<typename T>
void UnionFind<T>::AddPlayerToTeam(T* player, Team* team) {
    NodeUF<T>* playerNode = tablePlayers.insert(player);
    NodeUF<T>* headTeamNode = team->get_head_player();
    playerNode->_father = headTeamNode;
    headTeamNode->_size += 1;
}

template<typename T>
Team* teamPurchase(Team* BuyingTeam,Team* BoughtTeam) {

    NodeUF<T>* teamHeadBuyer = BuyingTeam->get_head_player();
    NodeUF<T>* teamHeadBought = BoughtTeam->get_head_player();

    //Making changes based on the different sizes of the two teams.
    if (teamHeadBuyer->_size >= teamHeadBought->_size)
    {
        teamHeadBought->_father = teamHeadBuyer;
        teamHeadBuyer->_size += teamHeadBought->_size;

        //changes to set_spiritToUpdate if buyer is bigger or equal in size
        //BoughtTeam->set_spiritToUpdate_right(BuyingTeam->get_tea_chronological_spirit());
        /*
         *Daniel: im trying
         */

        permutation_t originBoughtToUpdate = BoughtTeam->get_spiritToUpdate();

        /*
         * -------------------------------------
         */
        BoughtTeam->set_spiritToUpdate_left(BuyingTeam->get_tea_chronological_spirit());//Daniel: I changed to left
        /*
         * Daniel: we didn't think about the new players at the new big team
         *          that how I tried to fix it:
         */

        BuyingTeam->set_tea_spirit_right((originBoughtToUpdate*BoughtTeam->get_tea_chronological_spirit()));//
        //BuyingTeam->set_tea_spirit_right((BoughtTeam->get_tea_chronological_spirit()));//2th try


        /*
         * --------------------------------------------------------
         */

        //changes in set_gamesPlayedToUpdate for smaller team
        BoughtTeam->set_gamesPlayedToUpdate(-(BuyingTeam-> get_gamesPlayedToUpdate()));



        return BuyingTeam;
    }
    else {

        teamHeadBuyer->_father = teamHeadBought;
        teamHeadBought->_size += teamHeadBuyer->_size;

        // we are changing here the team id and so it could fuck up the process of finding the team later in the trees,

        //changes to set_spiritToUpdate if buyer is smaller
        BoughtTeam->set_tea_id(BuyingTeam->get_tea_id());
        //BoughtTeam->set_spiritToUpdate_right(BuyingTeam->get_tea_chronological_spirit());
        BoughtTeam->set_spiritToUpdate_left((BuyingTeam->get_spiritToUpdate()*BuyingTeam->get_tea_chronological_spirit()));//Daniel: I changed to left

        //two chNFWS firat one is this ^ secondonew is to mKE SURWE TI UPDte xhrobologicL QHWN UNITING
        // BuyingTeam->set_spiritToUpdate_right(BoughtTeam->get_tea_chronological_spirit().inv());
        BuyingTeam->set_spiritToUpdate_left(BoughtTeam->get_spiritToUpdate().inv());//Daniel: It should be BUY.TOUPDATE.inv

        //changes in set_gamesPlayedToUpdate for smaller team
        BuyingTeam->set_gamesPlayedToUpdate(-BoughtTeam-> get_gamesPlayedToUpdate());


        return BoughtTeam;
    }
}


template<typename T>
T* UnionFind<T>::Find(int playerId) {
    //check that exists in hash table
    try{
        tablePlayers[playerId];
    } catch (const MissingKey& e){
        return nullptr;
    }

    NodeUF* tmp1 = tablePlayers[playerId];
    NodeUF* tmp2 = tmp1;

    T * playerPointer = tmp1->_data;

    permutation_t sumSpirit = permutation_t::neutral(); //tmp1->_data->get_spirit();
    //Daniel: initial to neutral
    int sumGames = 0 ;// = tmp1->_data->get_indv_nu_games();

    if(tmp1->_team != nullptr)
    {
        sumSpirit = (tmp1->_team->get_spiritToUpdate())*sumSpirit;
        sumGames += tmp1->_team->get_gamesPlayedToUpdate();
    }
    tmp1 = tmp1->_father ;
    while(tmp1 && tmp1->_father)
    {
        sumSpirit = (tmp1->_team->get_spiritToUpdate())*sumSpirit;
        sumGames += tmp1->_team->get_gamesPlayedToUpdate();
        tmp1 = tmp1->_father;
    }

    while(tmp2->_father)
    {
        NodeUF<T>* next = tmp2->_father;

        if(tmp2->_team == nullptr)
        {
            //spirit
            tmp2->_data->set_left_spirit_chronological(sumSpirit);

            //games
            tmp2->_data->set_games(sumGames);

            //move node
            tmp2->_father = tmp1;
        }
        else
        {
            //spirit
            sumSpirit = sumSpirit*(tmp2->_team->get_spiritToUpdate().inv());
            tmp2->_team->set_spiritToUpdate_left(sumSpirit);//maybe problem

            //games
            sumGames -= tmp2->_team->get_gamesPlayedToUpdate();
            tmp2->_team->set_gamesPlayedToUpdate(sumGames);

            //move node
            tmp2->_father = tmp1;
        }
        tmp2 = next;
    }

    return playerPointer;
}

//template<typename T>
//bool UnionFind<T>::exists(int playerId) {
//    try{
//        tablePlayers[playerId];
//    } catch (const OutOfRange& e){
//        return false;
//    }
//    return true;
//}


//template<typename T>
//bool UnionFind<T>::teamDead(int playerId) {
//    NodeUF<T>* playerNode = tablePlayers[playerId];
//    while(playerNode->_father)
//        playerNode = playerNode->_father;
//    return !(playerNode->_team->get_alive());
//}


//template<typename T>
//permutation_t UnionFind<T>::SumSpirit(T* player) {
//
//    NodeUF* node = tablePlayers[player->get_player_id()];
//    permutation_t SumSpirit = player->get_spirit();
//
//    if(node->_team != nullptr)
//    {
//        SumSpirit = node->_team->get_spiritToUpdate()*SumSpirit;
//    }
//    NodeUF* fatherNode = node->_father;
//    while (fatherNode)//Daniel: we have here the same problem as at gamesplayed
//    {
//        SumSpirit = fatherNode->_team->get_spiritToUpdate()*SumSpirit;
//        fatherNode = fatherNode->_father;
//    }
//    //SumSpirit = node->_team->get_spiritToUpdate()*SumSpirit;
//    return SumSpirit;
//}


template<typename T>
int UnionFind<T>::SumGames(T* player) {
    NodeUF<T>* PlayerNode = tablePlayers[player->get_player_id()];
    int SumGames = player->get_indv_nu_games();

    if(PlayerNode->_team != nullptr)
    {
        SumGames += PlayerNode->_team->get_gamesPlayedToUpdate();
    }
    NodeUF<T>* fatherNode = PlayerNode->_father;
    while (fatherNode)
    {
        SumGames += fatherNode->_team->get_gamesPlayedToUpdate();
        fatherNode = fatherNode->_father;
    }
    return SumGames;
}

template<typename T>
void UnionFind<T>::removeAllPlayers(){
    tablePlayers.emptyDataFromTable();
}


#endif //TEA_CPP_UNIONFIND_H
