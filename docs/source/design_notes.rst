************
Design Notes
************

TensorRepresentation
====================

To convert an operator into a tensor in she some basis set the target API is:

.. code:: c++

   // Two-center
   Tensor TensorRepresentation(bra, operator, ket);

   // Three-center
   Tensor TensorRepresentation(bra, operator, ket1, ket2);
   // or
   Tensor TensorRepresentation(bra1, bra2, operator, ket);

   // Four-center
   Tensor TensorRepresentation(bra1, bra2, operator, ket1, ket2);

Focusing on only the AO basis set for the moment we have ``AOSpace<T>``
instances and ``SparseAOSpace<T>`` instances. For a four-center integral like
``I("mu,nu;lambda,sigma")`` we need to take two ``AOSpace<T>`` and
two ``SparseAOSpace<T>`` instances (note that which two modes are dependent
and which two are independent is determined by the types of the AO spaces
provided). This gives us :math:`2^N` overloads for an :math:`N`-center integral.
If we add derived spaces into the mix (so we can do transfomrations) this
becomes :math:`4^N` overloads (there's normal and sparse versions of derived
space too). This doesn't even take precision (i.e. double vs float) into account.
Asking module developers to handle all of these overloads is infeasible. Instead
we distinguish between the following scenarios:

#. All ``type::ao_space<T>``

   - This is the base case which maps directly to a call to an integral library
   - Handled by property type ``AOTensorRepresentation``

#. Mix of ``type::sparse_ao_space<T>`` and ``type::ao_space<T>`` instances

   - This is what happens when we use ToTs
   - The module will likely dispatch to an "all ``AOSpace<T>`` submodule and
     then fill in the ToT appropriately
   - Handled by property type ``GeneralAOTensorRepresentation``

#. One or more ``type::derived_spaceD``

   - Will probably dispatch to scenario 1, then do the transform
   -

#. At least one ``type::ind_derived_spaceD`` or ``type::dep_derived_spaceD``

   - Will probably dispatch to scenario 2, then do the transform


For scenario 1 it's pretty easy to have the API we want and we define the
property type's API:

.. code-block:: c++

   template<typename OperatorType, typename T>
   type::tensor AOTensorRepresentation(type::ao_space<T>,
                                     OperatorType,
                                     type::ao_space<T>)

For scenarios 2-4 we provide a free function (for API symmetry the free function
also works with scenario 1):

.. code-block:: c++

   template<typename...Args>
   auto TensorRepresentation(sde::Module& mod, Args&&...args)

which is used like:

.. code-block:: c++

   // Two center call
   auto x = TensorRepresentation(mod, bra, op, ket);

   // Four center call
   auto x = TensorRepresentation(mode, bra1, bra2, op, ket1, ket2);

This function takes a module to call, the bra(s), the operator, and the ket(s).
Internally it then packages the arguments based on type (``type::ao_space<T>``
vs ``type::derived_spaceD`` vs...), calls the module, and returns the result.

The actual property type API for scenarios 2 is:

.. code-block:: c++

   template<typeanme T>
   using sparse_map = std::map<unsigned int, type::sparse_ao_space<T>>;

   template<typename T>
   using dense_map  = std::map<unsigned int, type::ao_space<T>>;

   template<typename OperatorType, typename ElementType>
   type::tensor_of_tensors
   GeneralAOTensorRepresentation(sparse_map<ElementType>,
                                 dense_map<ElementType>,
                                 OperatorType);

where the maps map from tensor mode to AO spaces, e.g. sparse_map[1] is the
AO space for the 1-st mode of the output tensor (if `sparse_map.count(1) == 0`
then mode 1 isn't sparse...). The property type API for scenarios 3 and 4 are
similar. For scenario 3:

.. code-block:: c++

   template<typeanme T>
   using ao_space_map = std::map<unsigned int, type::ao_space<T>>;

   template<typename T>
   using derived_map  = std::map<unsigned int, type::derived_space<T>>;

   template<typename OperatorType, typename ElementType>
   type::tensor TransformedTensorRepresentation(ao_space_map<ElementType>,
                                                derived_map<ElementType>,
                                                OperatorType);

and for scenario 4:

.. code-block:: c++

   template<typeanme T>
   using ao_space_map = std::map<unsigned int, type::ao_space<T>>;

   template<typename T>
   using sparse_ao_map = std::map<unsigned int, type::sparse_ao_space<T>>;

   template<typename T>
   using ind_derived_map  = std::map<unsigned int, type::ind_derived_space<T>>;

   template<typename T>
   using dep_derived_map = std::map<unsigned int, type::dep_derived_space<T>>;

   template<typename OperatorType, typename ElementType>
   type::tensor GeneralTransformedTensorRepresentation(ao_space_map<ElementType>,
                                                sparse_ao_space<ElementType>,
                                                ind_derived_map<ElementType>,
                                                dep_derived_map<ElementType>,
                                                OperatorType);
