#! /bin/sh

run_test() {
	local test_script=$1
	local description=$2
	echo "Running test: $description"

	bash_out=$(echo "$test_script" | bash --posix)
	bash_exit_code=$?

	_42sh_out=$(echo "$test_script" | ./a.out)
	_42sh_exit_code=$?

	test1=0
	test2=0

	if [ "$bash_out" == "$_42sh_out" ]; then
		test1=1
		#echo "PASS: Outputs are identical."
	else
		echo ""
		echo "FAIL: Outputs differ."
		echo ""
		echo "bash: $bash_out"
		echo "42sh: $_42sh_out"
		echo ""
	fi

	if [ $bash_exit_code -eq $_42sh_exit_code ]; then
		test2=1
		#echo "PASS: Exit codes match."
	else
		echo "FAIL: Exit codes differ."
		echo ""
		echo "bash: $bash_exit_code"
		echo "42sh: $_42sh_exit_code"
	fi

	if [ "$test1" == "$test2" ]; then
		if [ $test1 -eq 1 ]; then
			echo "PASSED"
		fi
	fi

	echo "-------------------------"
}

run_test "seq 5" "simple seq"

run_test "echo Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Egestas purus viverra accumsan in nisl nisi. At quis risus sed vulputate. Neque laoreet suspendisse interdum consectetur libero. Et molestie ac feugiat sed lectus vestibulum mattis. Tristique nulla aliquet enim tortor at auctor. Aliquet porttitor lacus luctus accumsan tortor. Tellus cras adipiscing enim eu turpis. Mattis ullamcorper velit sed ullamcorper morbi tincidunt ornare. Nec sagittis aliquam malesuada bibendum arcu vitae elementum. Consequat id porta nibh venenatis cras. Dolor magna eget est lorem ipsum. Vivamus at augue eget arcu dictum varius duis. Aliquam eleifend mi in nulla. Cursus risus at ultrices mi tempus imperdiet nulla malesuada. Adipiscing elit ut aliquam purus sit amet luctus venenatis. Risus at ultrices mi tempus imperdiet nulla malesuada pellentesque elit. Mauris cursus mattis molestie a iaculis at erat pellentesque adipiscing." "many_args"

run_test "echo +Loremipsumdolorsitamet,consecteturadipiscingelit.Aliquamconsequatmassasedurnavenenatisbibendum.Praesentavariusenim,necvehiculanulla.Utatlectusaliquam,consecteturmagnased,suscipitipsum.Maurisnecmaurisex.Utsednullasuscipit,ultricieserossed,laciniaurna.Maecenassagittis,metusnonrhoncusplacerat,nisirisusinterdummi,egetviverraurnaeratsedvelit.Utpellentesquenequeex.Nullaullamcorpervelpurusvelsagittis.Vivamusatconsequatsem.Inlaciniasednequequisrhoncus.Classaptenttacitisociosquadlitoratorquentperconubianostra,perinceptoshimenaeos.Nuncfeugiatarcununc,utefficiturauguevehiculased.Morbisodales,urnasitametlaoreetimperdiet,justodiamconsequatmauris,necsuscipitenimtortorvitaesapien.Quisqueexmauris,tempusnecdolorquis,egestasornareerat.Donecvitaeultriceseros.Donecacloremposuere,scelerisqueestid,laoreetligula.Inimperdietjustosedvehiculadignissim.Nuncutligulaeudolorbibendumconsequatineutortor.Integerornaresuscipitnuncvelullamcorper.Vestibulumdapibusnisldapibusscelerisqueconvallis.Nullamfeugiatliberononjustoornare,atvenenatislectusmollis.Maecenasefficitureniminurnaconguesodales.Nullamporttitoruterosasagittis.Fuscenonorcivulputate,vulputatenequeiaculis,vestibulumodio.Donecscelerisque,tellussitametpulvinarpretium,erattelluscursusvelit,utsemperduieratveljusto.Inaterosatarcuaccumsanaliquetsitametuturna.Donectellusante,mollissedantetincidunt,sempervehiculaest.Utcondimentum,nisieuvestibulumullamcorper,enimtortormollisfelis,avulputateenimdiamvitaetortor.Vivamuseumiacligulacondimentumaliquet.Utegethendreritarcu.Vestibulumindolorpellentesque,tinciduntmagnaat,bibendumdolor.Insagittis,justoetfringilladapibus,nislurnalaciniaorci,quismalesuadaliberolectusindui.Aliquamvehiculaliberoinplaceratsemper.Etiamrhoncus,duietelementumcursus,tellusnibhpellentesquenunc,intristiquenibhsapienneclectus.Donecpulvinaraliquamconvallis.Orcivariusnatoquepenatibusetmagnisdisparturientmontes,nasceturridiculusmus.Namexdui,consequatidfacilisissitamet,temporeutellus.Inhachabitasseplateadictumst.Donecveleleifendfelis.Inconsecteturblanditmalesuada.Suspendisseegetsagittisurna.Vestibulumsollicitudinaccumsanligula,nonbibendumdiamcommodoquis.Sedegetinterdumnisi,sitametvolutpatleo.Quisqueidporttitorsem.Proinidlacusnectortorvolutpatultriciesutideros.Etiamaliquetnisiutnequeblanditdapibus.Sedfaucibusmollisluctus.Innibhmassa,condimentumvitaenisiquis,venenatisfaucibusjusto.Duisfaucibusexodio,necultricieseroslaciniaquis.Etiamafermentumtellus.Quisquemalesuadafelissedsapienporttitorluctus.Aliquameratvolutpat.Morbiporttitornislidexgravidaeuismod.Maecenaspharetraerosnondiamtinciduntaliquamateudolor.Utiaculisvehiculanisi,idiaculisarculuctusvitae.Aliquameratvolutpat.Namidtortoreuarcuportaaccumsanconvallisvelelit.Proinenimarcu,sagittisnecenimin,viverraiaculisdiam.Quisquemaximusconsequateuismod.Ututantequisturpisfaucibuselementumnonneclacus.Sedidelitarcu.Morbinullaligula,blanditaeleifendvel,volutpatnonquam.Quisqueelementumornarenulla,condimentumcommodoleovulputatesitamet.Duistortordui,consecteturvitaesapiennec,semperdignissimorci.Orcivariusnatoquepenatibusetmagnisdisparturientmontes,nasceturridiculusmus.Vivamusaccumsanelitsem,eudapibustellusconguevel.Suspendissealiquamantenecmassapharetravenenatis.Sedrhoncussollicitudinelementum.Maecenasegestas,nibhidmattispharetra,liberoestpulvinarerat,nontinciduntenimodiosollicitudinlacus.Maecenasfinibuslaoreetorciquisposuere.Suspendisseornaretempusaugue,velposueremassaconvalliseget.Craspellentesquenibhipsum,etdapibusnequesempersed.Orcivariusnatoquepenatibusetmagnisdisparturientmontes,nasceturridiculusmus.Curabiturrhoncusexatesttempor,velaliquetelittristique.Fusceintellusegetmagnafermentummollis.Proinegetconguemi.Quisquenonvelitdolor.Vivamuseratquam,rhoncusvitaeloremac,laciniamolestiemassa.Incongueconsecteturmassa,etiaculisenim.Aeneanaccumsanmauristellus,etcommodoodiovulputateeu.Fuscedignissimornarealiquet.Praesentlobortisegetloremvelvehicula.Curabiturvehiculaenimquiseratvestibulum,vitaecursusligulalaoreet.Pellentesquelectusmauris,aliquameumagnanon,maximusplaceratmauris.Donecfacilisiseratorci,eurhoncusrisusvulputatelacinia.Sedtinciduntipsumipsum,nonplaceratnislscelerisqueid.Crassodalesnibhvelsapiencondimentumlobortis.Phaselluseuantetortor.Aliquamatelitmi.Maecenastemporaccumsansapien,amalesuadaerosfaucibusnon.Etiamauctor,lacuseusit.Loremipsumdolorsitamet,consecteturadipiscingelit.Aliquamconsequatmassasedurnavenenatisbibendum.Praesentavariusenim,necvehiculanulla.Utatlectusaliquam,consecteturmagnased,suscipitipsum.Maurisnecmaurisex.Utsednullasuscipit,ultricieserossed,laciniaurna.Maecenassagittis,metusnonrhoncusplacerat,nisirisusinterdummi,egetviverraurnaeratsedvelit.Utpellentesquenequeex.Nullaullamcorpervelpurusvelsagittis.Vivamusatconsequatsem.Inlaciniasednequequisrhoncus.Classaptenttacitisociosquadlitoratorquentperconubianostra,perinceptoshimenaeos.Nuncfeugiatarcununc,utefficiturauguevehiculased.Morbisodales,urnasitametlaoreetimperdiet,justodiamconsequatmauris,necsuscipitenimtortorvitaesapien.Quisqueexmauris,tempusnecdolorquis,egestasornareerat.Donecvitaeultriceseros.Donecacloremposuere,scelerisqueestid,laoreetligula.Inimperdietjustosedvehiculadignissim.Nuncutligulaeudolorbibendumconsequatineutortor.Integerornaresuscipitnuncvelullamcorper.Vestibulumdapibusnisldapibusscelerisqueconvallis.Nullamfeugiatliberononjustoornare,atvenenatislectusmollis.Maecenasefficitureniminurnaconguesodales.Nullamporttitoruterosasagittis.Fuscenonorcivulputate,vulputatenequeiaculis,vestibulumodio.Donecscelerisque,tellussitametpulvinarpretium,erattelluscursusvelit,utsemperduieratveljusto.Inaterosatarcuaccumsanaliquetsitametuturna.Donectellusante,mollissedantetincidunt,sempervehiculaest.Utcondimentum,nisieuvestibulumullamcorper,enimtortormollisfelis,avulputateenimdiamvitaetortor.Vivamuseumiacligulacondimentumaliquet.Utegethendreritarcu.Vestibulumindolorpellentesque,tinciduntmagnaat,bibendumdolor.Insagittis,justoetfringilladapibus,nislurnalaciniaorci,quismalesuadaliberolectusindui.Aliquamvehiculaliberoinplaceratsemper.Etiamrhoncus,duietelementumcursus,tellusnibhpellentesquenunc,intristiquenibhsapienneclectus.Donecpulvinaraliquamconvallis.Orcivariusnatoquepenatibusetmagnisdisparturientmontes,nasceturridiculusmus.Namexdui,consequatidfacilisissitamet,temporeutellus.Inhachabitasseplateadictumst.Donecveleleifendfelis.Inconsecteturblanditmalesuada.Suspendisseegetsagittisurna.Vestibulumsollicitudinaccumsanligula,nonbibendumdiamcommodoquis.Sedegetinterdumnisi,sitametvolutpatleo.Quisqueidporttitorsem.Proinidlacusnectortorvolutpatultriciesutideros.Etiamaliquetnisiutnequeblanditdapibus.Sedfaucibusmollisluctus.Innibhmassa,condimentumvitaenisiquis,venenatisfaucibusjusto.Duisfaucibusexodio,necultricieseroslaciniaquis.Etiamafermentumtellus.Quisquemalesuadafelissedsapienporttitorluctus.Aliquameratvolutpat.Morbiporttitornislidexgravidaeuismod.Maecenaspharetraerosnondiamtinciduntaliquamateudolor.Utiaculisvehiculanisi,idiaculisarculuctusvitae.Aliquameratvolutpat.Namidtortoreuarcuportaaccumsanconvallisvelelit.Proinenimarcu,sagittisnecenimin,viverraiaculisdiam.Quisquemaximusconsequateuismod.Ututantequisturpisfaucibuselementumnonneclacus.Sedidelitarcu.Morbinullaligula,blanditaeleifendvel,volutpatnonquam.Quisqueelementumornarenulla,condimentumcommodoleovulputatesitamet.Duistortordui,consecteturvitaesapiennec,semperdignissimorci.Orcivariusnatoquepenatibusetmagnisdisparturientmontes,nasceturridiculusmus.Vivamusaccumsanelitsem,eudapibustellusconguevel.Suspendissealiquamantenecmassapharetravenenatis.Sedrhoncussollicitudinelementum.Maecenasegestas,nibhidmattispharetra,liberoestpulvinarerat,nontinciduntenimodiosollicitudinlacus.Maecenasfinibuslaoreetorciquisposuere.Suspendisseornaretempusaugue,velposueremassaconvalliseget.Craspellentesquenibhipsum,etdapibusnequesempersed.Orcivariusnatoquepenatibusetmagnisdisparturientmontes,nasceturridiculusmus.Curabiturrhoncusexatesttempor,velaliquetelittristique.Fusceintellusegetmagnafermentummollis.Proinegetconguemi.Quisquenonvelitdolor.Vivamuseratquam,rhoncusvitaeloremac,laciniamolestiemassa.Incongueconsecteturmassa,etiaculisenim.Aeneanaccumsanmauristellus,etcommodoodiovulputateeu.Fuscedignissimornarealiquet.Praesentlobortisegetloremvelvehicula.Curabiturvehiculaenimquiseratvestibulum,vitaecursusligulalaoreet.Pellentesquelectusmauris,aliquameumagnanon,maximusplaceratmauris.Donecfacilisiseratorci,eurhoncusrisusvulputatelacinia.Sedtinciduntipsumipsum,nonplaceratnislscelerisqueid.Crassodalesnibhvelsapiencondimentumlobortis.Phaselluseuantetortor.Aliquamatelitmi.Maecenastemporaccumsansapien,amalesuadaerosfaucibusnon.Etiamauctor,lacuseusit." "big arg"

run_test "" "non existant"

run_test "echo hello

echo byebye" "2 nl between echo"

run_test "echo hello | tr e a | grep hal" "pipe"

run_test "echo not#first" "comment: not first"

run_test "if echo if else then; then echo fi; fi" "colliding key words"

run_test "if true; then if true; then echo hello; fi; fi" "embedded ifs 1"

run_test "if true; then if true; then if true; then echo hello; fi; fi; fi" "embedded ifs 2"

run_test "if cat hello.txt; then echo inside if; echo bye bye; fi" "if and command"

run_test "if false; then echo false; fi" "if false"

run_test "if false; then echo false; else echo true; fi" "if false else"

run_test "if true; then echo false; else echo true; fi" "if true else"

run_test "if true; then echo hello; fi
if true; then echo nono; else echo yeye; fi" "2 ifs"

run_test "''" "empty single quotes"

run_test "echo ''" "empty quotes"

run_test "seq '1' '' '5'" "multiple quotes"

run_test "echo 'simple quote'" "simple quote"

run_test "echo '           '" "spaces as args"

run_test "echo '      argueux     '" "spaces as args"

run_test "echo -neennne 42\\nsh" "echo mix options 2"

echo "All tests completed."
