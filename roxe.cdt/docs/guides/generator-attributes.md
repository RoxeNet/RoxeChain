## ABI/Code generator attributes
Unlike the old ABI generator tool, the new tool uses C++11 or GNU style attributes to mark ```actions``` and ```tables```.
#### [[roxe::action]]
This attribute marks either a struct or a method as an action.
Example (four ways to declare an action for ABI generation):
```c++
// this is the C++11 and greater style attribute
[[roxe::action]]
void testa( name n ) {
   // do something
}

// this is the GNU style attribute, this can be used in C code and prior to C++ 11
__attribute__((roxe_action))
void testa( name n ){
   // do something
}

struct [[roxe::action]] testa {
   name n;
   ROXELIB_SERIALIZE( testa, (n) )
};

struct __attribute__((roxe_action)) testa {
   name n;
   ROXELIB_SERIALIZE( testa, (n) )
};
```
If your action name is not a valid [ROXE name](https://developers.eos.io/roxe-cpp/docs/naming-conventions) you can explicitly specify the name in the attribute ```c++ [[roxe::action("<valid action name>")]]```

#### [[roxe::table]]
Example (two ways to declare a table for ABI generation):
```
struct [[roxe::table]] testtable {
   uint64_t owner;
   /* all other fields */
};

struct __attribute__((roxe_table)) testtable {
   uint64_t owner;
   /* all other fields */
};

typedef roxe::multi_index<"tablename"_n, testtable> testtable_t;
```
If you don't want to use the multi-index you can explicitly specify the name in the attribute ```c++ [[roxe::table("<valid action name>")]]```.

#### [[roxe::contract("\<any name you like\>")]]
```
class [[roxe::contract("<any name you would like>")]] test_contract : public roxe::contract {
};
```
This will mark this `class` as being an `ROXE` contract, this allows for namespacing of contracts, i.e. you can include headers like `roxe::token` and not have `roxe::token`'s actions/tables wind up in you ABI or generated dispatcher.

#### [[roxe::on_notify("\<valid roxe account name\>::\<valid roxe action name\>")]]
```
[[roxe::on_notify("roxe.token::transfer")]]
void on_token_transfer(name from, name to, asset quantity, std::string memo) {
   do something on transfer from roxe.token...
}

[[roxe::on_notify("*::transfer")]]
void on_any_transfer(name from, name to, asset quantity, std::string memo) {
   do something on transfer from any account...
}
```

#### [[roxe::wasm_entry]]
```
[[roxe::wasm_entry]]
void some_function(...) {
   do something...
}
```

This will mark an arbitrary function as an entry point, which will then wrap the function with global constructors (ctors) and global destructors (dtors).  This will allow for the roxe.cdt toolchain to produce WASM binaries for other ecosystems.

#### [[roxe::wasm_import]]
```
extern "C" {
   __attribute__((roxe_wasm_import))
   void some_intrinsic(...);
}
```

This will mark a function declaration as being a WebAssembly import.  This allows for other compilation modes to specify which functions are import only (i.e. do not link) without having to maintain a secondary file with duplicate declarations.

### Fixing an ABI or Writing an ABI Manually
- Advanced features of the newest version of the ABI will require manual construction of the ABI, and odd and advanced C++ patterns could capsize the generators type deductions. So having a good knowledge of how to write an ABI should be an essential piece of knowledge of a smart contract writer.
- Please refer to [developers.eos.io "How to Write an ABI File"](https://developers.eos.io/roxe-cpp/docs/how-to-write-an-abi) to learn about the different sections of an ABI.

### Adding Ricardian Contracts and Clauses to ABI
- As of ROXE.CDT v1.4.0 the ABI generator will try to automatically import contracts and clauses into the generated ABI.  There are a few caveats to this, one is a strict naming policy of the files and an HTML tag used to mark each Ricardian contract and each clause.
- The Ricardian contracts should be housed in a file with the name <contract name>.contracts.md and the clauses should be in a file named <contract name>.clauses.md.
 - For each Ricardian contract the header `<h1 class="contract">ActionName</h1>` should be used, as this directs the ABI generator to attach this Ricardian contract to the specified action.
 - For each Ricardian clause the header `<h1 class="clause">ClauseID</h1>` should be used, as this directs the ABI generator to the clause id and the subsequent body.
 - The option `-R` has been added to roxe-cpp and roxe-abigen to add "resource" paths to search from, so you can place these files in any directory structure you like and use `-R<path to file>` in the same vein as `-I` for include paths.
 - To see these in use please see ./examples/hello/hello.contracts.md and ./examples/hello/hello.clauses.md.
