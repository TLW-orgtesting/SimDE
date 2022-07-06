/*TUTORIAL
 *
 * This tutorial walks you through creating a simple module which will compute
 * the Coulombic repulsion of the nuclei using a trivial implementation. The
 * quantity computed by this module is thus an energy and we will design our
 * module so that it satisfies the ``Energy`` property type.
 *
 * We start the tutorial by declaring the class which will implement our module.
 * All classes implementing modules must inherit from ``sde::ModuleBase`` and
 * thus we need to include ``sde/module_base.hpp``, which contains the
 * declaration of the ``sde::ModuleBase`` class.
 *
 * .. note::
 *
 *     Typically one would declare the class in a header file, but since this
 *     class is only used in this tutorial we have declared and implemented it
 *     in a source file so that the tutorial is self-contained.
 */
#include <sde/module_base.hpp>

/*TUTORIAL
 *
 * Rigorously speaking a module only needs to implement the ``run_`` function.
 * If you forget to you'll get a compiler error. That said, most modules will
 * also need a constructor to setup there state. Since this state defines the
 * default state of your module it should be the same for all instances of the
 * module and defined in a default constructor.
 *
 * The entire declaration of our module follows.
 */
class NuclearRepulsion : public sde::ModuleBase {
public:
    // Default ctor, defines the default state of the module
    NuclearRepulsion();

    // This signature is boilerplate, just copy/paste it
    sde::type::result_map run_(sde::type::input_map inputs,
                               sde::type::submodule_map) const override;
}; // class NuclearRepulsion

/*TUTORIAL
 *
 * The above declaration would normally go in a header file. The remainder of
 * this tutorial is the implementation and would normally go in the source file.
 * We now need to implement our module. Since our module ultimately computes an
 * energy we need to include the ``Energy`` property type which is contained in
 * the ``property_types/energy.hpp`` header file.
 */
#include <property_types/energy.hpp>

/*TUTORIAL
 *
 * Next, we implement our constructor.
 */
NuclearRepulsion::NuclearRepulsion() : ModuleBase(this) {
    /*TUTORIAL
     *
     * The first thing one usually does in the ctor is to set the property types
     * that the module satisfies. If your module satisfies multiple property
     * types simply call ``satisfies_property_type`` multiple times, once for
     * each property type.
     *
     * .. note::
     *
     *     The ``Energy`` property type is templated on the type used to hold
     *     the energy. For the purposes of this tutorial we assume that we are
     *     only concerned with double precision, but you should probably make
     *     your module work with other precisions.
     */
    satisfies_property_type<property_types::Energy<double>>();

    /*TUTORIAL
     *
     * The above function automatically adds the Energy property type's fields
     * to our API. Specifically our module now takes a ``LibChemist::Molecule``
     * class instance, and an integer signifying the derivative order to
     * compute and returns a ``TA::TSpArray`` with the energy derivative.
     *
     * If we want to add any additional input/results to our class we do that
     * here. In anticipation of eventually doing some screening we add a
     * distance threshold (which we will ignore for now).
     */
    add_input<double>("Distance Threshold")
      .set_description("Minimum distance for neglecting a pair's interaction")
      .set_default(1.0E10);

    /*TUTORIAL
     *
     * If you want to add additional results the syntax is the same, except
     * the initial function call is ``add_result`` instead of ``add_input``.
     *
     * With our module's input/result fields defined. The remainder of the
     * ctor implementation is dedicated to meta-data about your module. For
     * example giving a brief description of what it does and a list of papers
     * to cite.
     */
    description("Computes nucleus-nucleus repulsion");
    citation("Coulomb, Charles-Augustin de. "
             "Premier mémoire sur l’électricité et le magnétisme. 1785");

} // NuclearRepulsion::NuclearRepulsion()

/*TUTORIAL
 *
 * With the constructor implemented all that remains is to implement the run
 * function. The run function takes two maps: one with the inputs the user
 * provided and one with the submodules requested (our current module does not
 * use submodules) and returns a map of all computed results.
 */
sde::type::result_map NuclearRepulsion::run_(sde::type::input_map inputs,
                                             sde::type::submodule_map) const {
    /*TUTORIAL
     *
     * The first step in all modules is to unwrap the inputs. This can be done
     * via the property type classes that the module satisfies. If your module
     * takes inputs not affiliated with a property type you'll have to unwrap
     * them manually, like we do for the ``"Distance Threshold"``.
     */
    using energy_type       = property_types::Energy<double>;
    const auto [mol, deriv] = energy_type::unwrap_inputs(inputs);

    auto thresh = inputs.at("Distance Threshold").value<double>();

    /*TUTORIAL
     *
     * With our inputs available we implement our algorithm. This part is SDE
     * agnostic.
     */
    double enuc = 0.0;
    for(const auto& atomi : mol) {
        const auto& ri = atomi.coords();
        for(const auto& atomj : mol) {
            if(atomi == atomj) break;
            const auto& rj    = atomj.coords();
            const double ZiZj = atomi.Z() * atomj.Z();
            const std::array rij{ri[0] - rj[0], ri[1] - rj[1], ri[2] - rj[2]};
            const double rij2 =
              rij[0] * rij[0] + rij[1] * rij[1] + rij[2] * rij[2];
            const double mag_rij = std::sqrt(rij2);
            enuc += ZiZj / mag_rij;
        }
    }

    /*TUTORIAL
     *
     * With the energy computed all that remains is to package it up and return
     * the results in the agreed upon format, which is a ``TA::TSpArray`. The
     * actual packaging of a single scalar into a ``TA::TSpArray`` is a rather
     * laborious task and omitted here.
     */
    property_types::type::tensor<double> rv;
    auto r = results();
    return Energy<double>::wrap_results(results(), r);
} // NuclearRepulsion::run_
