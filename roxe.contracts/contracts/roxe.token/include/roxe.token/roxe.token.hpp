#pragma once

#include <roxe/asset.hpp>
#include <roxe/roxe.hpp>

#include <string>

namespace roxesystem {
   class system_contract;
}

namespace roxe {

   using std::string;

   /**
    * roxe.token contract defines the structures and actions that allow users to create, issue, and manage
    * tokens on roxe based blockchains.
    */
   class [[roxe::contract("roxe.token")]] token : public contract {
      public:
         using contract::contract;

         /**
          * Allows `issuer` account to create a token in supply of `maximum_supply`. If validation is successful a new entry in statstable for token symbol scope gets created.
          *
          * @param issuer - the account that creates the token,
          * @param maximum_supply - the maximum supply set for the token created.
          *
          * @pre Token symbol has to be valid,
          * @pre Token symbol must not be already created,
          * @pre maximum_supply has to be smaller than the maximum supply allowed by the system: 1^62 - 1.
          * @pre Maximum supply must be positive;
          */
         [[roxe::action]]
         void create( const name&   issuer,
                      const asset&  maximum_supply);
         /**
          *  This action issues to `to` account a `quantity` of tokens.
          *
          * @param to - the account to issue tokens to, it must be the same as the issuer,
          * @param quntity - the amount of tokens to be issued,
          * @memo - the memo string that accompanies the token issue transaction.
          */
         [[roxe::action]]
         void issue( const name& to, const asset& quantity, const string& memo );

         /**
          * The opposite for create action, if all validations succeed,
          * it debits the statstable.supply amount.
          *
          * @param quantity - the quantity of tokens to retire,
          * @param memo - the memo string to accompany the transaction.
          */
         [[roxe::action]]
         void retire( const asset& quantity, const string& memo );

         /**
          * Allows `from` account to transfer to `to` account the `quantity` tokens.
          * One account is debited and the other is credited with quantity tokens.
          *
          * @param from - the account to transfer from,
          * @param to - the account to be transferred to,
          * @param quantity - the quantity of tokens to be transferred,
          * @param memo - the memo string to accompany the transaction.
          */
         [[roxe::action]]
         void transfer( const name&    from,
                        const name&    to,
                        const asset&   quantity,
                        const string&  memo );
         /**
          * Allows `ram_payer` to create an account `owner` with zero balance for
          * token `symbol` at the expense of `ram_payer`.
          *
          * @param owner - the account to be created,
          * @param symbol - the token to be payed with by `ram_payer`,
          * @param ram_payer - the account that supports the cost of this action.
          *
          * More information can be read [here](https://github.com/ROXE/roxe.contracts/issues/62)
          * and [here](https://github.com/ROXE/roxe.contracts/issues/61).
          */
         [[roxe::action]]
         void open( const name& owner, const symbol& symbol, const name& ram_payer );

         /**
          * This action is the opposite for open, it closes the account `owner`
          * for token `symbol`.
          *
          * @param owner - the owner account to execute the close action for,
          * @param symbol - the symbol of the token to execute the close action for.
          *
          * @pre The pair of owner plus symbol has to exist otherwise no action is executed,
          * @pre If the pair of owner plus symbol exists, the balance has to be zero.
          */
         [[roxe::action]]
         void close( const name& owner, const symbol& symbol );

         /**
          * Set transaction fee `fee` for token `symbol` only by owner account `owner`.
          *
          * @param owner - the account to be authorization,
          * @param symbol - the token to be payed,
          * @param fee - the number that supports the cost of each transaction.
          *
          */
         [[roxe::action]]   ///FIXME add transaction fee
         void setfee( const name& owner, const symbol& symbol, const int64_t fee );

         static asset get_supply( const name& token_contract_account, const symbol_code& sym_code )
         {
            stats statstable( token_contract_account, sym_code.raw() );
            const auto& st = statstable.get( sym_code.raw() );
            return st.supply;
         }

         static asset get_balance( const name& token_contract_account, const name& owner, const symbol_code& sym_code )
         {
            accounts accountstable( token_contract_account, owner.value );
            const auto& ac = accountstable.get( sym_code.raw() );
            return ac.balance;
         }

         using create_action = roxe::action_wrapper<"create"_n, &token::create>;
         using issue_action = roxe::action_wrapper<"issue"_n, &token::issue>;
         using retire_action = roxe::action_wrapper<"retire"_n, &token::retire>;
         using transfer_action = roxe::action_wrapper<"transfer"_n, &token::transfer>;
         using open_action = roxe::action_wrapper<"open"_n, &token::open>;
         using close_action = roxe::action_wrapper<"close"_n, &token::close>;
//         using setfee_action = roxe::action_wrapper<"setfee"_n, &token::setfee>;
      private:
         struct [[roxe::table]] account {
            asset    balance;

            uint64_t primary_key()const { return balance.symbol.code().raw(); }
         };

         struct [[roxe::table]] currency_stats {
            asset    supply;
            asset    max_supply;
            name     issuer;
            int64_t  fee;

            uint64_t primary_key()const { return supply.symbol.code().raw(); }
         };

         typedef roxe::multi_index< "accounts"_n, account > accounts;
         typedef roxe::multi_index< "stat"_n, currency_stats > stats;

         void sub_balance( const name& owner, const asset& value );
         void add_balance( const name& owner, const asset& value, const name& ram_payer );

      public:
         /**
          * default transaction fee
          */
          static constexpr int64_t default_tx_fee = 1;    // actural fee = tx_fee / precision =1/10000 (0.0001)

   };

}
