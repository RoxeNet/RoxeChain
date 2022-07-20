#pragma once

#include <roxe/asset.hpp>
#include <roxe/roxe.hpp>

#include <string>
#include <vector>

#include <roxe.system/roxe.system.hpp>

//namespace roxesystem {
//    class system_contract;
//}

namespace roxe {

    using std::string;
    using std::vector;
    using std::find;

    using roxesystem::system_contract;

    /**
     * roxe.tokenize contract defines the structures and actions that allow users to create, issue, and manage
     * tokens on roxe based blockchains.
     */
    class [[roxe::contract("roxe.tokenize")]] tokenize : public contract {
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
        void create(const name &issuer,
                    const asset &maximum_supply);

        /**
         *  This action issues to `to` account a `quantity` of tokens.
         *
         * @param from - the account to be authorized to issue tokens,
         * @param to - the account to issue tokens to,
         * @param quntity - the amount of tokens to be issued,
         * @memo - the memo string that accompanies the token issue transaction.
         */
        [[roxe::action]]
        void issue(const name &from, const name &to, const asset &quantity, const string &memo);

        /**
         * The opposite for create action, if all validations succeed,
         * it debits the statstable.supply amount.
         *
         * @param from - the account of tokens to retire,
         * @param quantity - the quantity of tokens to retire,
         * @param memo - the memo string to accompany the transaction.
         */
        [[roxe::action]]
        void retire(const name &from, const asset &quantity, const string &memo);

        /**
         * add author for issuer
         *
         * @param author - the account of authorization ,
         * @param sym - the symbol of tokens,
         */
        [[roxe::action]]
        void addauthor(const symbol &sym, const name &author);

        /**
         * delete author for issuer
         * @param author - the account of authorization ,
         * @param sym - the symbol of tokens,
         */
        [[roxe::action]]
        void delauthor(const symbol &sym, const name &from);

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
        void transfer(const name &from,
                      const name &to,
                      const asset &quantity,
                      const string &memo);

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
        void open(const name &owner, const symbol &symbol, const name &ram_payer);

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
        void close(const name &owner, const symbol &symbol);

        /**
         * Set transaction fee `fee` for token `symbol`.
         *
         * @param symbol - the token to be payed,
         * @param fee - the number that supports the cost of each transaction.
         *
         */
        [[roxe::action]]   ///FIXME add transaction fee
        void setfee(const symbol &symbol, const int64_t fee);


        /**
         * Set transaction fee percent `percent` for token `symbol`.
         *
         * @param symbol - the token to be payed,
         * @param percent - the percent that supports the fee percent of each transaction.
         *
         */
        [[roxe::action]]   ///FIXME add transaction fee
        void setfeeper(const symbol &symbol, const int64_t percent);

        /**
         * Set transaction fee `max fee` for token `symbol`.
         *
         * @param symbol - the token to be payed,
         * @param maxfee - the percent that supports the max fee of each transaction.
         *
         */
        [[roxe::action]]   ///FIXME add transaction fee
        void setmaxfee(const symbol &symbol, const int64_t maxfee);

        /**
         * Set transaction fee `min fee` for token `symbol`.
         *
         * @param symbol - the token to be payed,
         * @param minfee - the percent that supports the min fee of each transaction.
         *
         */
        [[roxe::action]]   ///FIXME add transaction fee
        void setminfee(const symbol &symbol, const int64_t minfee);

        /**
              * Set transaction fee token `roc` for token `symbol`.
              *
              * @param symbol - the token to be payed,
              * @param roc - the useroc that supports the roc token fee of each transaction.
              *
              */
        [[roxe::action]]   ///FIXME add transaction fee
        void useroc(const symbol &symbol, const bool roc);

        /**
             * Set transaction fee fix or not for token `symbol`.
             *
             * @param symbol - the token to be payed,
             * @param fix - the setfix that supports fix fee of each transaction.
             *
             */
        [[roxe::action]]   ///FIXME fix transaction fee
        void setfix(const symbol &symbol, const bool fix);

        static asset get_supply(const name &token_contract_account, const symbol_code &sym_code) {
            stats statstable(token_contract_account, sym_code.raw());
            const auto &st = statstable.get(sym_code.raw());
            return st.supply;
        }

        static asset get_balance(const name &token_contract_account, const name &owner, const symbol_code &sym_code) {
            accounts accountstable(token_contract_account, owner.value);
            const auto &ac = accountstable.get(sym_code.raw());
            return ac.balance;
        }

        static asset estimate_fee_given_in(const name &token_contract_account, const asset &amount_in) {
            auto sym = amount_in.symbol;
            check(sym.is_valid(), "invalid symbol name");
            check(amount_in.is_valid(), "invalid supply");
            check(amount_in.amount > 0, "amount_in must be positive");

            stats statstable(token_contract_account, sym.code().raw());
            auto existing = statstable.find(sym.code().raw());
            check(existing != statstable.end(), "token with symbol not exists");
            const auto &st = statstable.get(sym.code().raw());
            symbol fee_sym = st.useroc ? system_contract::get_core_symbol() : st.supply.symbol;
            int64_t fee_amount;

            if(st.percent == 0){ /// FIXED FEE without Percent
                fee_amount = st.fee;
                if (fee_amount < st.minfee)
                    fee_amount = st.minfee;
                if (fee_amount > st.maxfee)
                    fee_amount = st.maxfee;
            }else{
                int64_t min_out,max_out;
                min_out = (st.minfee - st.fee) * percent_decimal / st.percent;
                max_out = (st.maxfee - st.fee) * percent_decimal / st.percent;
                if(amount_in.amount <= min_out + st.minfee){
                    fee_amount = st.minfee;
                }else if(amount_in.amount >= max_out + st.maxfee){
                    fee_amount = st.maxfee;
                }else{
                    // estimate fee increased by 1 when smaller than exact;
                    int64_t remainer = (st.fee * percent_decimal + amount_in.amount * st.percent) % (st.percent + percent_decimal);
                    fee_amount = (st.fee * percent_decimal + amount_in.amount * st.percent) / (st.percent + percent_decimal);
                    if(remainer){
                        fee_amount = fee_amount + 1;
                    }
                }
            }

            return asset(fee_amount, fee_sym);
        }

        static asset estimate_fee_given_out(const name &token_contract_account, const asset &amount_out) {
            auto sym = amount_out.symbol;
            check(sym.is_valid(), "invalid symbol name");
            check(amount_out.is_valid(), "invalid supply");
            check(amount_out.amount > 0, "amount_out must be positive");

            stats statstable(token_contract_account, sym.code().raw());
            auto existing = statstable.find(sym.code().raw());
            check(existing != statstable.end(), "token with symbol not exists");
            const auto &st = statstable.get(sym.code().raw());
            symbol fee_sym = st.useroc ? system_contract::get_core_symbol() : st.supply.symbol;
            int64_t fee_amount = st.fee + amount_out.amount * st.percent / percent_decimal;

            if (fee_amount < st.minfee)
                fee_amount = st.minfee;
            if (fee_amount > st.maxfee)
                fee_amount = st.maxfee;

            return asset(fee_amount, fee_sym);
        }

        using create_action = roxe::action_wrapper<"create"_n, &tokenize::create>;
        using issue_action = roxe::action_wrapper<"issue"_n, &tokenize::issue>;
        using retire_action = roxe::action_wrapper<"retire"_n, &tokenize::retire>;
        using transfer_action = roxe::action_wrapper<"transfer"_n, &tokenize::transfer>;
        using open_action = roxe::action_wrapper<"open"_n, &tokenize::open>;
        using close_action = roxe::action_wrapper<"close"_n, &tokenize::close>;
        using setfee_action = roxe::action_wrapper<"setfee"_n, &tokenize::setfee>;
    private:
        struct [[roxe::table]] account {
            asset balance;

            uint64_t primary_key() const { return balance.symbol.code().raw(); }
        };

        struct [[roxe::table]] currency_stats {
            asset supply;
            asset max_supply;
            name issuer;
            vector <name> authors;

            int64_t fee;
            bool fixed;
            int64_t percent;
            int64_t maxfee;
            int64_t minfee;
            bool useroc;

            uint64_t primary_key() const { return supply.symbol.code().raw(); }
            //ROXELIB_SERIALIZE(currency_stats,(supply)(max_supply)(issuer)(authors)(fee)(fixed)(percent)(maxfee)(minfee)(useroc))
        };

        typedef roxe::multi_index<"accounts"_n, account> accounts;
        typedef roxe::multi_index<"stat"_n, currency_stats> stats;

        void sub_balance(const name &owner, const asset &value);

        void add_balance(const name &owner, const asset &value, const name &ram_payer);

    public:
        /**
         * default transaction fee
         */
        static constexpr int64_t default_tx_fee = 0;    // actural fee = tx_fee / precision =1/10000 (0.0001)
        static constexpr int64_t percent_decimal = 1000000;
    };

}
