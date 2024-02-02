#! /bin/sh

flm_test() {
	local test_script=$1
	local description=$2
	echo "#!/bin/sh

    REF_OUT=\".refstd.out\"
    TEST_OUT=\".teststd.out\"
    REF_ERR=\".refstd.err\"
    TEST_ERR=\".teststd.err\"
    REF=\"bash --posix\"
    TEST=\"./../src/42sh\"

    COMMAND=$test_script
    echo \$COMMAND >in

    cat in | \$REF >\"\$REF_OUT\" 2>\"\$REF_ERR\"
    REF_CODE= \$?
    cat in | \$TEST >\"\$TEST_OUT\" 2>\"\$TEST_ERR\"
    TEST_CODE= \$?
    diff \"\$REF_OUT\" \"\$TEST_OUT\"
    DIFF_CODE=\$?

    if [ \$REF_CODE -ne \$TEST_CODE ]; then
        echo \"wrong return code\"
    fi

    if [ \$DIFF_CODE -ne 0 ]; then
        echo \"wrong stdout\"
    fi

    diff \"\$REF_ERR\" \"\$TEST_ERR\"
    ERR_CODE=\$?

    if [ \$ERR_CODE -ne 0 ]; then
        echo \"wrong stderr\"
    fi

    rm \$REF_OUT
    rm \$TEST_OUT
    rm \$REF_ERR
    rm \$TEST_ERR
    rm in

    exit \$DIFF_CODE && \$ERR_CODE && [ \$REF_CODE -eq \$TEST_CODE]" >${description}.sh
}

flm_test "seq 5" "simple seq"

flm_test "echo Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Egestas purus viverra accumsan in nisl nisi. At quis risus sed vulputate. Neque laoreet suspendisse interdum consectetur libero. Et molestie ac feugiat sed lectus vestibulum mattis. Tristique nulla aliquet enim tortor at auctor. Aliquet porttitor lacus luctus accumsan tortor. Tellus cras adipiscing enim eu turpis. Mattis ullamcorper velit sed ullamcorper morbi tincidunt ornare. Nec sagittis aliquam malesuada bibendum arcu vitae elementum. Consequat id porta nibh venenatis cras. Dolor magna eget est lorem ipsum. Vivamus at augue eget arcu dictum varius duis. Aliquam eleifend mi in nulla. Cursus risus at ultrices mi tempus imperdiet nulla malesuada. Adipiscing elit ut aliquam purus sit amet luctus venenatis. Risus at ultrices mi tempus imperdiet nulla malesuada pellentesque elit. Mauris cursus mattis molestie a iaculis at erat pellentesque adipiscing." "many_args"

flm_test "echo +Loremipsumdolorsitamet,consecteturadipiscingelit.Aliquamconsequatmassasedurnavenenatisbibendum.Praesentavariusenim,necvehiculanulla.Utatlectusaliquam,consecteturmagnased,suscipitipsum.Maurisnecmaurisex.Utsednullasuscipit,ultricieserossed,laciniaurna.Maecenassagittis,metusnonrhoncusplacerat,nisirisusinterdummi,egetviverraurnaeratsedvelit.Utpellentesquenequeex.Nullaullamcorpervelpurusvelsagittis.Vivamusatconsequatsem.Inlaciniasednequequisrhoncus.Classaptenttacitisociosquadlitoratorquentperconubianostra,perinceptoshimenaeos.Nuncfeugiatarcununc,utefficiturauguevehiculased.Morbisodales,urnasitametlaoreetimperdiet,justodiamconsequatmauris,necsuscipitenimtortorvitaesapien.Quisqueexmauris,tempusnecdolorquis,egestasornareerat.Donecvitaeultriceseros.Donecacloremposuere,scelerisqueestid,laoreetligula.Inimperdietjustosedvehiculadignissim.Nuncutligulaeudolorbibendumconsequatineutortor.Integerornaresuscipitnuncvelullamcorper.Vestibulumdapibusnisldapibusscelerisqueconvallis.Nullamfeugiatliberononjustoornare,atvenenatislectusmollis.Maecenasefficitureniminurnaconguesodales.Nullamporttitoruterosasagittis.Fuscenonorcivulputate,vulputatenequeiaculis,vestibulumodio.Donecscelerisque,tellussitametpulvinarpretium,erattelluscursusvelit,utsemperduieratveljusto.Inaterosatarcuaccumsanaliquetsitametuturna.Donectellusante,mollissedantetincidunt,sempervehiculaest.Utcondimentum,nisieuvestibulumullamcorper,enimtortormollisfelis,avulputateenimdiamvitaetortor.Vivamuseumiacligulacondimentumaliquet.Utegethendreritarcu.Vestibulumindolorpellentesque,tinciduntmagnaat,bibendumdolor.Insagittis,justoetfringilladapibus,nislurnalaciniaorci,quismalesuadaliberolectusindui.Aliquamvehiculaliberoinplaceratsemper.Etiamrhoncus,duietelementumcursus,tellusnibhpellentesquenunc,intristiquenibhsapienneclectus.Donecpulvinaraliquamconvallis.Orcivariusnatoquepenatibusetmagnisdisparturientmontes,nasceturridiculusmus.Namexdui,consequatidfacilisissitamet,temporeutellus.Inhachabitasseplateadictumst.Donecveleleifendfelis.Inconsecteturblanditmalesuada.Suspendisseegetsagittisurna.Vestibulumsollicitudinaccumsanligula,nonbibendumdiamcommodoquis.Sedegetinterdumnisi,sitametvolutpatleo.Quisqueidporttitorsem.Proinidlacusnectortorvolutpatultriciesutideros.Etiamaliquetnisiutnequeblanditdapibus.Sedfaucibusmollisluctus.Innibhmassa,condimentumvitaenisiquis,venenatisfaucibusjusto.Duisfaucibusexodio,necultricieseroslaciniaquis.Etiamafermentumtellus.Quisquemalesuadafelissedsapienporttitorluctus.Aliquameratvolutpat.Morbiporttitornislidexgravidaeuismod.Maecenaspharetraerosnondiamtinciduntaliquamateudolor.Utiaculisvehiculanisi,idiaculisarculuctusvitae.Aliquameratvolutpat.Namidtortoreuarcuportaaccumsanconvallisvelelit.Proinenimarcu,sagittisnecenimin,viverraiaculisdiam.Quisquemaximusconsequateuismod.Ututantequisturpisfaucibuselementumnonneclacus.Sedidelitarcu.Morbinullaligula,blanditaeleifendvel,volutpatnonquam.Quisqueelementumornarenulla,condimentumcommodoleovulputatesitamet.Duistortordui,consecteturvitaesapiennec,semperdignissimorci.Orcivariusnatoquepenatibusetmagnisdisparturientmontes,nasceturridiculusmus.Vivamusaccumsanelitsem,eudapibustellusconguevel.Suspendissealiquamantenecmassapharetravenenatis.Sedrhoncussollicitudinelementum.Maecenasegestas,nibhidmattispharetra,liberoestpulvinarerat,nontinciduntenimodiosollicitudinlacus.Maecenasfinibuslaoreetorciquisposuere.Suspendisseornaretempusaugue,velposueremassaconvalliseget.Craspellentesquenibhipsum,etdapibusnequesempersed.Orcivariusnatoquepenatibusetmagnisdisparturientmontes,nasceturridiculusmus.Curabiturrhoncusexatesttempor,velaliquetelittristique.Fusceintellusegetmagnafermentummollis.Proinegetconguemi.Quisquenonvelitdolor.Vivamuseratquam,rhoncusvitaeloremac,laciniamolestiemassa.Incongueconsecteturmassa,etiaculisenim.Aeneanaccumsanmauristellus,etcommodoodiovulputateeu.Fuscedignissimornarealiquet.Praesentlobortisegetloremvelvehicula.Curabiturvehiculaenimquiseratvestibulum,vitaecursusligulalaoreet.Pellentesquelectusmauris,aliquameumagnanon,maximusplaceratmauris.Donecfacilisiseratorci,eurhoncusrisusvulputatelacinia.Sedtinciduntipsumipsum,nonplaceratnislscelerisqueid.Crassodalesnibhvelsapiencondimentumlobortis.Phaselluseuantetortor.Aliquamatelitmi.Maecenastemporaccumsansapien,amalesuadaerosfaucibusnon.Etiamauctor,lacuseusit.Loremipsumdolorsitamet,consecteturadipiscingelit.Aliquamconsequatmassasedurnavenenatisbibendum.Praesentavariusenim,necvehiculanulla.Utatlectusaliquam,consecteturmagnased,suscipitipsum.Maurisnecmaurisex.Utsednullasuscipit,ultricieserossed,laciniaurna.Maecenassagittis,metusnonrhoncusplacerat,nisirisusinterdummi,egetviverraurnaeratsedvelit.Utpellentesquenequeex.Nullaullamcorpervelpurusvelsagittis.Vivamusatconsequatsem.Inlaciniasednequequisrhoncus.Classaptenttacitisociosquadlitoratorquentperconubianostra,perinceptoshimenaeos.Nuncfeugiatarcununc,utefficiturauguevehiculased.Morbisodales,urnasitametlaoreetimperdiet,justodiamconsequatmauris,necsuscipitenimtortorvitaesapien.Quisqueexmauris,tempusnecdolorquis,egestasornareerat.Donecvitaeultriceseros.Donecacloremposuere,scelerisqueestid,laoreetligula.Inimperdietjustosedvehiculadignissim.Nuncutligulaeudolorbibendumconsequatineutortor.Integerornaresuscipitnuncvelullamcorper.Vestibulumdapibusnisldapibusscelerisqueconvallis.Nullamfeugiatliberononjustoornare,atvenenatislectusmollis.Maecenasefficitureniminurnaconguesodales.Nullamporttitoruterosasagittis.Fuscenonorcivulputate,vulputatenequeiaculis,vestibulumodio.Donecscelerisque,tellussitametpulvinarpretium,erattelluscursusvelit,utsemperduieratveljusto.Inaterosatarcuaccumsanaliquetsitametuturna.Donectellusante,mollissedantetincidunt,sempervehiculaest.Utcondimentum,nisieuvestibulumullamcorper,enimtortormollisfelis,avulputateenimdiamvitaetortor.Vivamuseumiacligulacondimentumaliquet.Utegethendreritarcu.Vestibulumindolorpellentesque,tinciduntmagnaat,bibendumdolor.Insagittis,justoetfringilladapibus,nislurnalaciniaorci,quismalesuadaliberolectusindui.Aliquamvehiculaliberoinplaceratsemper.Etiamrhoncus,duietelementumcursus,tellusnibhpellentesquenunc,intristiquenibhsapienneclectus.Donecpulvinaraliquamconvallis.Orcivariusnatoquepenatibusetmagnisdisparturientmontes,nasceturridiculusmus.Namexdui,consequatidfacilisissitamet,temporeutellus.Inhachabitasseplateadictumst.Donecveleleifendfelis.Inconsecteturblanditmalesuada.Suspendisseegetsagittisurna.Vestibulumsollicitudinaccumsanligula,nonbibendumdiamcommodoquis.Sedegetinterdumnisi,sitametvolutpatleo.Quisqueidporttitorsem.Proinidlacusnectortorvolutpatultriciesutideros.Etiamaliquetnisiutnequeblanditdapibus.Sedfaucibusmollisluctus.Innibhmassa,condimentumvitaenisiquis,venenatisfaucibusjusto.Duisfaucibusexodio,necultricieseroslaciniaquis.Etiamafermentumtellus.Quisquemalesuadafelissedsapienporttitorluctus.Aliquameratvolutpat.Morbiporttitornislidexgravidaeuismod.Maecenaspharetraerosnondiamtinciduntaliquamateudolor.Utiaculisvehiculanisi,idiaculisarculuctusvitae.Aliquameratvolutpat.Namidtortoreuarcuportaaccumsanconvallisvelelit.Proinenimarcu,sagittisnecenimin,viverraiaculisdiam.Quisquemaximusconsequateuismod.Ututantequisturpisfaucibuselementumnonneclacus.Sedidelitarcu.Morbinullaligula,blanditaeleifendvel,volutpatnonquam.Quisqueelementumornarenulla,condimentumcommodoleovulputatesitamet.Duistortordui,consecteturvitaesapiennec,semperdignissimorci.Orcivariusnatoquepenatibusetmagnisdisparturientmontes,nasceturridiculusmus.Vivamusaccumsanelitsem,eudapibustellusconguevel.Suspendissealiquamantenecmassapharetravenenatis.Sedrhoncussollicitudinelementum.Maecenasegestas,nibhidmattispharetra,liberoestpulvinarerat,nontinciduntenimodiosollicitudinlacus.Maecenasfinibuslaoreetorciquisposuere.Suspendisseornaretempusaugue,velposueremassaconvalliseget.Craspellentesquenibhipsum,etdapibusnequesempersed.Orcivariusnatoquepenatibusetmagnisdisparturientmontes,nasceturridiculusmus.Curabiturrhoncusexatesttempor,velaliquetelittristique.Fusceintellusegetmagnafermentummollis.Proinegetconguemi.Quisquenonvelitdolor.Vivamuseratquam,rhoncusvitaeloremac,laciniamolestiemassa.Incongueconsecteturmassa,etiaculisenim.Aeneanaccumsanmauristellus,etcommodoodiovulputateeu.Fuscedignissimornarealiquet.Praesentlobortisegetloremvelvehicula.Curabiturvehiculaenimquiseratvestibulum,vitaecursusligulalaoreet.Pellentesquelectusmauris,aliquameumagnanon,maximusplaceratmauris.Donecfacilisiseratorci,eurhoncusrisusvulputatelacinia.Sedtinciduntipsumipsum,nonplaceratnislscelerisqueid.Crassodalesnibhvelsapiencondimentumlobortis.Phaselluseuantetortor.Aliquamatelitmi.Maecenastemporaccumsansapien,amalesuadaerosfaucibusnon.Etiamauctor,lacuseusit." "big arg"

flm_test "" "non existant"

flm_test "echo hello

echo byebye" "2 nl between echo"

flm_test "echo hello | tr e a | grep hal" "pipe"

flm_test "echo not#first" "comment: not first"

flm_test "if echo if else then; then echo fi; fi" "colliding key words"

flm_test "if true; then if true; then echo hello; fi; fi" "embedded ifs 1"

flm_test "if true; then if true; then if true; then echo hello; fi; fi; fi" "embedded ifs 2"

flm_test "if cat hello.txt; then echo inside if; echo bye bye; fi" "if and command"

flm_test "if false; then echo false; fi" "if false"

flm_test "if false; then echo false; else echo true; fi" "if false else"

flm_test "if true; then echo false; else echo true; fi" "if true else"

flm_test "if true; then echo hello; fi
if true; then echo nono; else echo yeye; fi" "2 ifs"

flm_test "''" "empty single quotes"

flm_test "echo ''" "empty quotes"

flm_test "seq '1' '' '5'" "multiple quotes"

flm_test "echo 'simple quote'" "simple quote"

flm_test "echo '           '" "spaces as args"

flm_test "echo '      argueux     '" "spaces as args"

flm_test "echo -neennne 42\\nsh" "echo mix options 2"

flm_test "echo 'simple single quotes'" "simple single quotes"

flm_test "echo 'spaces between single quotes'" "spaces between single quotes"

flm_test "echo 'This is a test with\'escaped\' single quote.'" "single quotes with escaped single quote"

flm_test "echo 'single quote at the start'" "single quote at the start"

flm_test "echo 'single quote at the end'" "single quote at the end"

flm_test "echo 'This is a test with\tescaped\t tab inside single quotes.'" "single quotes with escaped tab"

flm_test "echo "simple double quotes"" "simple double quotes"

flm_test "echo "spaces between double quotes"" "spaces between double quotes"

flm_test "echo "This is a test with\"escaped\" double quote."" "double quotes with escaped double quote"

flm_test "echo "double quote at the start"" "double quote at the start"

flm_test "echo "double quote at the end"" "double quote at the end"

flm_test "echo "This is a test with\tescaped\t tab inside double quotes."" "double quotes with escaped tab"

flm_test "echo 'Single quotes with "double quotes" inside.'" "single quotes with double quotes inside"

flm_test "echo "Double quotes with 'single quotes' inside."" "double quotes with single quotes inside"

flm_test "echo 'Mix of single quotes and double quotes: "Hello" and 'World''" "mix of single and double quotes"
