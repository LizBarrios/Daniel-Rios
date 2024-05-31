# Paradigma de programacion funcional, reporte de practica 3 con SML.

### Introducción

El enfoque de programación funcional busca abordar la computación como una evaluación de funciones matemáticas, evitando el cambio de estado y datos mutables. En este paradigma, las funciones son tratadas como elementos principales, pudiendo ser asignadas a variables, pasadas como argumentos y retornadas como valores. Se investigó este enfoque a través del lenguaje de programación Standard ML (SML).

### Ejercicios de la práctica. Siguiendo el tour de SML.

#### Ejercicio 1.1 Let expressions
El SML define una expresión 'let', en la que se pueden hacer declaraciones de alcance.

Fuera de estas expresiones, sus definiciones quedan libres. El resultado de evaluar una expresión let, por ejemplo `letexpr` aquí, es la última expresión contenida en in...end.
```sml
val lexpr =
  let val x = 1
      val y = 2
  in x + y
  end

(* REPL *)
(* - x;
 * stdIn:13.1 Error: unbound variable or constructor: x *)
```
![SML](/imagenes/SML1.1.png)


#### Ejercicio 1.2 Basic data types
En SML, los tipos de datos básicos son S: unit, bool, int, real, string, and char.

```sml
(* Unit -- has only one value: () *)
val u : unit = ()

(* Booleans : bool *)
val b : bool = true

(* Integers : int *)
val i : int = 1

(* Note that negation is performed using a tilde *)
val iNegative = ~1

(* Floating point numbers : real *)
val r : real = 2.0

(* Note that negation is performed using a tilde *)
val rNegative = ~2.0

(* Strings : string *)
val s : string = "s"

(* ASCII Characters : char *)
val c : char = #"c"
```
![SML](/imagenes/SML1.2.png)


#### Ejercicio 1.3 Built-in data structures

```sml
(* Tuples *)
val t : (int * int) =
    (1, 2)

(* Lists *)
val l : int list =
    [1, 2, 3]

(* Records *)
val r : {name:string, occupation:string} =
    {name="Zaphod Beeblebrox", occupation="President of the Galaxy"}

val tupleField1      = #1 t
val zaphodsOccuption = #occupation r
val tuplesAreRecords = {1="Hello", 2="world"} = ("Hello", "world")

```
![SML](/imagenes/SML1.3.png)


#### Ejercicio 1.4 Functions
Las funciones se declaran usando `fn` y se les puede dar un nombre con `val`. Todas las funciones toman un argumento y se cursan.

Para declarar una función con múltiples argumentos, use múltiples funciones.

`inc'` aplica parcialmente agregar a 1, para crear una nueva función. Esto tiene el mismo comportamiento que inc.

```sml
val inc : int -> int =
    fn y =>
        1 + y

val add : int -> int -> int =
    fn x => fn y =>
        x + y

val inc' : int -> int =
    add 1

val t = (inc' 1) = (inc 1) (* true *)
```
![SML](/imagenes/SML1.4.png)


### Ejercicio 1.5 Fun with Functions
Como es más difícil trabajar con la forma `fn` de argumento único, existe `add`, que tiene el mismo comportamiento que el `add` anterior, pero con una definición más simple. A los argumentos de función se les pueden dar declaraciones de tipo si se desea, pero no son necesarias, ya que SML puede inferirlas.

Las funciones pueden aceptar un argumento tuplado para crear una función sin currículum y devolver cualquier número de resultados utilizando una tupla. Los argumentos tuplados pueden proporcionarse con declaraciones de tipo si se desea.

Todas las funciones en SML deben aceptar al menos un valor y producir al menos un valor, pero es posible que no las necesite, como en una función de impresión. En ese caso, puede aceptar un valor unitario como entrada y devolver la unidad (`()`) como resultado.

Consulte un operador, como `+`, utilizando la palabra clave `op`

```sml
fun add x y = x + y

fun sub (x: int) (y: int) = x - y

fun mul (x, y) = x * y

fun divide (x: int, y: int) = x div y

fun divmod (x: int, y: int): (int * int) = (x div y, x mod y)

fun printExample () : unit = print "Hello!\n"

val add' = (op +)
```
![SML](/imagenes/SML1.5.png)

#### Ejercicio 1.6 Modules
Cada programa SML se compone de módulos. Los módulos agrupan un conjunto de definiciones. Aquí, definimos un módulo llamado Módulos usando la palabra clave de estructura, con una definición, divertido número favorito `()`.

Este programa utiliza otros tres módulos: `String`, `Int` y `Random`.

Se abre la cadena, trayendo sus definiciones al entorno del módulo Módulos. La función `^` proviene del módulo `String` y concatena dos cadenas.
`Random` tiene el alias `R`, para acortar su uso y evitar contaminar el medio ambiente directamente con sus definiciones.
`Int` se usa directamente.

```sml
structure Modules = struct
  open String
  structure R = Random

  fun favouriteNum () =
      let val seed  = R.rand (0, 0)
          val myInt = R.randRange (0, 10) seed
      in print ("My favourite number is " ^ (Int.toString myInt) ^ "\n")
      end
end
```
![SML](/imagenes/SML1.6.png)


#### Ejercicio 1.7 Module Signatures
En SML, los módulos exponen todo su contenido de forma predeterminada, pero lo que se exporta se puede controlar definiendo una firma de las exportaciones. para el módulo.
```sml
(* REPL *)
- use "examples/mod-sigs.sml";
structure Math : sig val e : real end

- Math.e;
- val it = 2.7182 : real
- Math.pi;
stdIn:38.1-38.8 Error: unbound variable or constructor: pi in path Math.p
```
![SML](/imagenes/SML1.7.png)


#### Ejercicio 1.8 Signatures, continued
No es necesario que las firmas estén vinculadas a un módulo específico. Una firma puede definirse por separado y tener múltiples implementaciones.

```sml
signature GREETING = sig
  val greeting : string
end

structure EnglishGreeting : GREETING = struct
  val greeting = "Hello.\n"
end

structure ValyrianGreeting : GREETING = struct
  val greeting = "Valar morghulis.\n"
end

val u  = print EnglishGreeting.greeting
val u' = print ValyrianGreeting.greeting

```
![SML](/imagenes/SML1.8.png)


#### Ejercicio 1.9 Functors
Los módulos pueden aceptar otros módulos como parámetros, incluida la aceptación de una firma en lugar de una implementación específica. Estos se denominan functores y se declaran mediante la palabra clave funtor.
```sml
signature GREETING = sig
  val greeting : string
end

functor Greeter (G : GREETING) = struct
  fun greet () = print G.greeting
end

structure EnglishGreeting : GREETING = struct
  val greeting = "Hello.\n"
end

structure ValyrianGreeting : GREETING = struct
  val greeting = "Valar morghulis.\n"
end

structure englishGreeter = Greeter(EnglishGreeting)
structure essosGreeter = Greeter(ValyrianGreeting)

val u  = englishGreeter.greet ()
val u' = essosGreeter.greet ()
```
![SML](/imagenes/SML1.9.png)


#### Ejercicio 1.10 Defining data types
Los alias de tipo se pueden definir utilizando la palabra clave tipo.
Se pueden declarar nuevos tipos de datos utilizando la palabra clave `datatype`.

`major_arcana_card` declara un tipo, major_arcana_card, que es un par de nombre y número.

Los tipos de datos pueden consistir en múltiples casos exclusivos. `card_suit` declara un tipo con cuatro valores y `card_value` declara un tipo con catorce valores.

```sml
type major_arcana_card = (string * int)

datatype card_suit = swords | wands | cups | disks

datatype card_value = prince | princess | knight | queen
                    | one | two | three | four | five
                    | six | seven | eight | nine | ten

datatype minor_arcana_card = minor_arcana_card of
    { suit  : card_suit
    , value : card_value
    }

datatype tarot_card = major_arcana of major_arcana_card
                    | minor_arcana of minor_arcana_card

```
![SML](/imagenes/SML1.10.png)


#### Ejercicio 1.11 Recursive types
Los tipos pueden ser recursivos, lo que facilita la definición de estructuras de datos recursivas como listas o árboles. Por ejemplo, una lista de 'como se podría definir usando dos casos:

* Empty (vacio)
    * `eol`: un marcador de "fin de lista"
    * Definido en SML como `nil`
* o un elemento de tipo `'a`, seguido del resto de la lista de `'as`, que puede estar vacío
    * +: de 'a * 'una lista
    * Definido en SML como ::

Un árbol binario también podría definirse en dos casos:
* Una hoja
* Un nodo que contiene un elemento de tipo `'a` y dos subárboles, `izquierdo` y `derecho`
Los operadores definidos por el usuario, como `+`: usado aquí, se pueden convertir en infijos utilizables, es decir, entre dos argumentos, usando las palabras clave `infixr <N>` op e infix <N> op. Tomando la resta como ejemplo, por ejemplo, `3 - 4 - 5 - 6`:

* Si la resta se definiera en `infixr`, intentaría analizarla como `(3 - (4 - (5 - 6))) = ~2`
* Pero la resta se define como `infix`, por lo que en realidad se analiza como `(((3 - 4) - 5) - 6) = ~12`
  
`<N>` especifica cuán estrechamente se vinculan los operadores con sus argumentos. Dados dos operadores, `*` y `-`, y la expresión `3 * 4 - 5`:

* `infix 3 *, infix 4 -` se analizaría como `(3 * (4 - 5)) = ~3`
* `infix 4 *, infix 3 -` se analizaría como `((3 * 4) - 5) = 7`

```sml
infixr 4 +:
datatype 'a list = eol
                 | +: of 'a * 'a list

datatype 'a tree = leaf
                 | node of { value : 'a
                           , left  : 'a tree
                           , right : 'a tree
                           }

val ints = 1 +: 2 +: 3 +: eol
val inttree = node { value = 1
                   , left  = node { value = 2
                                  , left = leaf
                                  , right = leaf
                                  }
                   , right = node { value = 3
                                  , left = leaf
                                  , right = leaf
                                  }
                   }
```
![SML](/imagenes/SML1.11.png)


#### Ejercicio 2.0 Pattern matching
El SML permite establecer patrones de coincidencia de valores, proporcionando análisis de casos. Usando la funcion integrada `list` en SML, podríamos hacer coincidir patrones en sus casos y aplicar una función a cada valor de la lista.

* Si la lista está vacía (case `nil`), no hay nada que hacer: devolver la lista vacía.
* Si la lista tiene un elemento, `x`:
    * aplicar f a x
    * aplicar el mapa f al resto de la lista xs
    * cree una nueva lista del elemento transformado, x', y el resto   transformado de la lista, xs'
    * x' :: xs'

```sml
fun map f xs =
  case xs of
    nil     => nil
  | x :: xs =>
    let val x'  = f x
        val xs' = map f xs
    in x' :: xs'
    end

fun map' f nil       = nil
  | map' f (x :: xs) = f x :: map' f xs
```
![SML](/imagenes/SML2.0.png)


#### Ejercicio 2.1 Exhaustivity checking
La coincidencia de patrones proporciona una verificación exhaustiva de los casos de tipos de datos. Si omite un caso, el compilador emitirá una advertencia. Las opciones del compilador pueden convertir esto en un error.

```sml
fun inexhaustive nil = nil

(*
 * 02-01-exhaustive.sml:1.6-1.28 Warning: match nonexhaustive
            nil => ... *)
```
![SML](/imagenes/SML2.1.png)


#### Ejercicio 2.2 Value deconstruction
El SML también le permite deconstruir valores utilizando la palabra clave `val`, en lugar de utilizar la construcción `case`. Esto es útil en casos como extraer un valor de una lista, tupla o registro.

```sml
datatype dog = dog of { name : string }
val n = (1,2,3)
val (_,two,_) = n
val (x,y,z) = n

val charlie = dog { name = "Charlie" }
val lucky   = dog { name = "Lucky" }
val dog{name=pup1} = lucky
val dog{name=pup2} = charlie
val [_, second, _] = [1, 2, 3]

(* Type error *)
(* val (x,y) = n *)

```
![SML](/imagenes/SML2.2.png)


#### Ejercicio 2.3 Pattern matching in functions
Todo esto en conjunto hace que sea fácil expresar su problema como un conjunto de casos, que luego puede descomponer y componer para escribir su lógica.
```sml
open String

datatype player = mage of {name: string, magic_type: string}
                | warrior of {name: string, weapon: string}

fun greet_player (mage {name=name, magic_type=magic_type}) =
    print ("Greetings, " ^ name ^ ", master of the " ^ magic_type ^ "!\n")
  | greet_player (warrior {name=name, weapon=weapon}) =
    print ("Hullo, " ^ name ^ ", wielder of " ^ weapon ^ "!\n")

val u = greet_player (warrior {name="Grom", weapon="Gorehowl"})
```
![SML](/imagenes/SML2.3.png)


#### Ejercicio 2.4 Conditional expressions
El SML define una expresión condicional. Puede definir casos adicionales encadenando las expresiones `if-else`.

Tenga en cuenta que todas las ramas de la expresión if-else deben tener el mismo tipo.

```sml
val trueCond =
  if (1 = 1)
  then 1
  else 0

val elseCond =
  if (1 = 0)
  then 1
  else if (1 = 1)
  then ~1
  else 0

(* val error = if true then () else 1;
 * stdIn:16.1-16.23 Error: types of if branches do not agree [overload conflict]
    then branch: unit
    else branch: [int ty]
    in expression:
      if true then () else 1 *)
```
![SML](/imagenes/SML2.4.png)


#### Ejercicio 2.5 Recursion
>El SML fomenta la recursividad en lugar de la iteración; por ejemplo, para sumar una lista de números, usaría la recursividad. 

La especificación requiere que las funciones recursivas de cola se optimicen para no utilizar espacio de pila. `sum` aquí explotaría la pila con una lista lo suficientemente grande, pero `sum_iter` no lo haría y se ejecutaría tan rápido como un bucle imperativo.
```sml
fun sum []        = 0
  | sum (x :: xs) = x + sum xs

fun sum_iter xs =
  let fun sum_iter' [] acc        = acc
        | sum_iter' (x :: xs) acc = sum_iter' xs (x + acc)
  in sum_iter' xs 0
  end

val s = sum [1, 2, 3]
val s' = sum_iter [1, 2, 3]
```
![SML](/imagenes/SML2.5.png)


#### Ejercicio 2.6 Higher order functions
Con frecuencia, puede evitar la recursividad directa mediante el uso de funciones de orden superior: pasar una función a otra función, que luego maneja los detalles de la iteración o agregación utilizando la función pasada. Ejemplos incluyen:

> * `map f xs`, which applies a function f to each element in `xs`, creating a new list
> * `List.filter p xs`, which filters a list using a predicate p, creating a new list containing any items that returned true for `p x`
> * `foldr c s xs` lets you combine the items of a list to a summary value, using some combining operation `c` and `a `starting value `s`

```sml
val twos = map (fn x => x + 1) [1, 1, 1] (* [2, 2, 2] *)
val two  = List.filter (fn x => x mod 2 = 0) [1, 2, 3] (* [2] *)

(* NOTE: Actually builtin *)
fun foldr combiner aggregate nil       = aggregate
  | foldr combiner aggregate (x :: xs) =
    let val the_rest_combined = foldr combiner aggregate xs
    in combiner (x, the_rest_combined)
    end

val sum = foldr (op +) 0
val s = sum [1, 2, 3]

fun length xs = foldr (fn (_, count) => count + 1) 0 xs
val l = length [1, 2, 3]
```
![SML](/imagenes/SML2.6.png)


#### Ejercicio 2.7 Infinite loops
Los bucles infinitos se pueden expresar de forma segura mediante recursividad; Como se mencionó anteriormente, SML optimiza las llamadas finales.

```sml
fun forever () = forever ()

val _ = forever ()
(* Ctrl+C to terminate *)
``` 
![SML](/imagenes/SML2.7.png)


#### Ejercicio 2.8 Chaining expressions for side effects
En SML, todo es una expresión que devuelve un resultado, pero puede encadenar varias expresiones en forma imperativa para sus efectos secundarios separándolas por punto y coma. El resultado de estas cadenas es la última expresión del bloque.
```sml
val _ = (
    print "Hello!\n";
    print "Another line!\n"
)
```
![SML](/imagenes/SML2.8.png)


#### Ejercicio 2.9 Mutable references
Como se señaló anteriormente, todo en SML es inmutable de forma predeterminada. `val` le da un nombre a un valor. Así es como se usa más comúnmente SML y la mutabilidad es rara. A veces puede resultar útil tener una referencia mutable, por lo que SML proporciona la capacidad para hacerlo.

> Puede definir una referencia usando `ref`, obtener su valor usando `!` antes del nombre y configúrelo usando `:=`.

Las funciones pueden aceptar referencias como parámetros y esto se refleja en el tipo.

```sml
val x = ref 10
val y = ref 20

(* Although an 'assignment', returns unit, as assignment
 * is an expression and returns a value *)
val _ = x := !x + !y
val _ = !x (* 30 *)

fun ++ (x: int ref) : int = (
    x := !x + 1;
    !x (* Return the new value of x *)
)

val x = ref 0
val xNewState = ++x (* 1 *)
val xValue = !x (* 1 *)
```
![SML](/imagenes/SML2.9.png)


#### Ejercicio 2.10 While loops
El SML tiene un bucle `while`definido que puede usarse en lugar de recursividad o funciones de orden superior, en las que una expresión se repite mientras se cumple una condición.

Se tiende a preferir la recursividad y las funciones de orden superior, ya que `while` solo tiene sentido con una condición mutable, y SML tiende a preferir la inmutabilidad.
```sml
val x = ref 0

val u =
  while (!x) <> 10 do (
    x := !x + 1;
    print (Int.toString (!x));
    print "\n"
  )
```
![SML](/imagenes/SML2.10.png)


#### Ejercicio 3.0 Concurrent ML Introduction
> **Para los siguientes ejercicios se asume que se tiene instalado el paquete Concurrent ML (CML) en SML/NJ. CML es una extensión de SML que proporciona primitivas de concurrencia y comunicación.**


#### Ejercicio 3.1 Spawning a light-weight thread
`spawn` crea un hilo ligero administrado por el tiempo de ejecución de Concurrent ML.

```sml
fun say s =
  let val delay = Time.fromMilliseconds 100
      val i = ref 0
  in while (!i) < 5 do (
      OS.Process.sleep delay;
      print s;
      i := (!i) + 1
  )
  end

fun main () = (
    CML.spawn (fn () => say "World!\n");
    say "Hello!\n"
)

val _ = RunCML.doit (main, NONE)
```
![SML](/imagenes/SML3.1.png)


#### Ejercicio 3.2 Channels
Los canales son un conducto escrito a través del cual puede enviar y recibir valores con las funciones de envío y recepción de canal.
```sml
(*Enviar al canal ch*)
- enviar (ch, v);
(*Recibe de ch y dale un nombre v*)
- val v = recv ch;
```
Tenga en cuenta que `send` es una operación de bloqueo. No volverá hasta que otro hilo intente `rcv`.

```sml
fun sum s c = CML.send (c, foldr (op +) 0 s)

fun formatOutput x y =
  Int.toString x ^ " " ^ Int.toString y ^ " " ^ Int.toString (x + y) ^ "\n"

fun main () =
  let
    open String
    val s = [7, 2, 8, ~9, 4, 0]
    val ch = CML.channel ()
    val slen = (List.length s div 2)
    val x = ref 0
    val y = ref 0
  in (
    CML.spawn (fn () => sum (List.take (s, slen)) ch);
    CML.spawn (fn () => sum (List.drop (s, slen)) ch);
    x := CML.recv ch;
    y := CML.recv ch;
    print (formatOutput (!x) (!y))
  )
  end

val _ = RunCML.doit(main, NONE)
```
![SML](/imagenes/SML3.2.png)


#### Ejercicio 3.3 Select
`select` permite que un hilo espere en una lista de eventos de comunicación.
```sml
fun fib c q =
  let val x = ref 0
      val y = ref 1
      val nextFib = fn x' =>
        let val tmp = !x
        in (
            x := !y;
            y := tmp + (!y)
        )
        end
      val break = ref false
      fun endRecvd () = !break = true
  in
    while not (endRecvd ()) do
      CML.select
        [ CML.wrap (CML.sendEvt (c, !x), nextFib )
        , CML.wrap (CML.recvEvt q, fn _ => (
            break := true;
            print "quit\n"
          ))
        ]
  end

fun print_channel c q =
  let
    val i = ref 0
  in (
    while (!i) < 10 do (
      print (Int.toString (CML.recv c));
      print "\n";
      i := (!i) + 1
    );
    CML.send (q, true)
  )
  end

fun main () =
  let
    val c : int CML.chan = CML.channel ()
    val q : bool CML.chan = CML.channel ()
  in (
    CML.spawn (fn () => print_channel c q);
    fib c q
  )
  end

val _ = RunCML.doit(main, NONE)
```
![SML](/imagenes/SML3.3.png)


#### Ejercicio 3.4 Mailboxes
En una sección anterior utilizamos canales sincrónicos, pero CML proporciona canales asincrónicos con un envío sin bloqueo, llamados `Mailboxes`.
```sml
fun main () =
  let
    val m : int Mailbox.mbox = Mailbox.mailbox ()
  in (
    Mailbox.send (m, 10);
    Mailbox.recv m; (* 10 *)
    OS.Process.success
  )
  end

val _ = main ();
```
![SML](/imagenes/SML3.4.png)


#### Ejercicio 3.5 IVars
A veces es posible que necesite variables mutables y seguras para subprocesos. CML los ofrece en dos versiones.

Un `ivar` puede estar en uno de dos estados: `empty` o `full`. Un `ivar` se puede escribir una vez y proporciona sincronización en las lecturas. Una vez escrito, el `ivar` está full y las escrituras posteriores son un error.

Como es posible que aún no se haya puesto un valor, existe una operación sin bloqueo que devuelve una opción, `iGetPoll`.

Las variables `I` funcionan con el marco de eventos de CML y, por lo tanto, pueden ser una fuente de eventos para que los subprocesos `select`, si se accede a través de `iGetEvt`.
```sml
structure S = SyncVar
fun main () =
  let val i : int S.ivar = S.iVar ()
  in (
    S.iGetPoll i; (* NONE *)
    S.iPut (i, 10);
    S.iGetPoll i; (* SOME 10 *)
    S.iPut (i, 10);
    (* uncaught exception Put
         raised at: cml/src/core-cml/sync-var.sml:142.42-142.45 *)
    OS.Process.success
  )
  end
```
![SML](/imagenes/SML3.5.png)


#### Ejercicio 3.6 MVars
Las variables `M` son muy parecidas a las variables `I`, pero se pueden escribir en ellas varias veces. Escribir en una variable `M` completa es un error, pero tomar de una `mvar` borra su contenido. Puede obtener una variable `M` sin borrar su contenido usando `mGet`, o borrando su contenido usando `mTake`.

Las variables `M`proporcionan una integración similar con el marco de eventos como las variables `I`.
```sml
structure S = SyncVar
fun main () =
  let val i : int S.mvar = S.mVar ()
  in (
    S.mPut (i, 10);
    S.mGet i; (* 10 *)
    S.mPut (i, 10);
    (* uncaught exception Put
         raised at: cml/src/core-cml/sync-var.sml:203.42-203.45 *)
    S.mTake i; (* 10 *)
    S.mPut (i, 0);
    S.mGet i; (* 0 *)
    OS.Process.success
  )
  end
```
![SML](/imagenes/SML3.6.png)


### FIN DE LA PRACTICA 3