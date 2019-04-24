# os_lab1


<!-- saved from url=(0070)http://zemris.fer.hr/predmeti/os/pripreme/upute/prekidi_i_signali.html -->

<h1> PREKIDI I SIGNALI</h1>
<h3> Upute za laboratorijske vježbe</h3>


<div class="MsoNormal" align="center" style="text-align:center">

<hr size="1" width="100%" align="center">

</div>


<h2><span lang="hr">SIGNALI</span></h2>

<p><span lang="hr">Signali na razini procesa (pokrenutog programa) su analogni 
mehanizam sklopovskim prekidima na razini procesora. Služe za obradu nekih 
asinkronih događaja. Osnovna ideja je kao i kod prekida: proces nešto svoje radi 
dok se u nekom (neočekivanom) trenutku ne dogodi nešto što treba odmah obraditi. 
Stoga se pri primitku signala trenutni posao prekida, obrađuje se signal, te 
nastavlja s prekinutim poslom. Signal ne sadrži dodatne informacije (osim broja 
signala) - ako su one potrebne, treba ih dohvatiti u obradi signala. Signal 
procesu može poslati jezgra operacijska sustava (npr. SIGSEGV), drugi proces (npr. 
SIGTERM) ili proces sam sebi (npr. SIGALRM uz odgodu ili neki drugi događaj). 
Proces može programirati svoje ponašanje za signal: - može ga prihvatiti i 
obraditi pretpostavljenom funkcijom (većinom to znači prekid procesa) - može ga 
prihvatiti i obraditi funkcijom zadanom u programu (u programu je definirano što 
će se obaviti po primitku takvog signala) - može ga se zadržati (zapamtiti, ali 
ne i odmah obraditi) - može ga se ignorirati (odbaciti bez obrade). Izuzetak od 
navedenih pravila je SIGKILL koji ubija proces (SIGKILL ignorira postavke koje 
je program postavio).&nbsp; </span></p>
<p>Kada se prihvati signal, pozove se funkcija za obradu signala. Slično kao i 
kod prekida na razini procesora, i pri prihvatu signala zabranjuje se daljnje 
prekidanje, ali samo s tim signalom - drugi signali mogu prekinuti tu obradu. Po 
završektu obrade ponovno se dozvoljava prekidanje s tim signalom te se 
eventualno zadržani signali (došli za vrijeme obrade) sada propuštaju. Signali 
koji se procesu upute za vrijeme obrade prethodnog signala istog tipa - isti 
broj, stavljaju se u red i čekaju. S time da se pamti samo po jedan signal istog 
tipa. Primjerice, ako procesu za vrijeme obrade signala SIGINT dođu još tri 
takva signala, zapamtit će se samo prvi takav signal. Po završetku obrade prvog 
signala SIGINT ponovno će se pozvati ista funkcija, ali samo jednom (uz 
prepostavku da za vrijeme ove druge obrade nije došao novi signal SIGINT). </p>
<p>Signali su standardni mehanizam na UNIX operacijskim sustavima i njemu 
sličnim (npr. Linux). Operacijski sustavi Windows imaju minimalnu podršku za 
signale i u mnogočemu su različiti (zapravo se oni ne koriste).</p>
<span lang="hr">

<h3>Signali i sučelja za upravljanje signalima</h3>

<p>Moderne implementacije UNIX-a definiraju oko tridesetak signala. Ovdje je
pregled samo istaknutijih signala, dok potpun popis daje <tt><span style="font-size:
10.0pt;font-family:&quot;Courier New&quot;">
<a href="http://www.opengroup.org/onlinepubs/009695399/basedefs/signal.h.html">man 
-s 3HEAD signal</a></span></tt>:</p>

<div align="center">

<table border="0" cellpadding="0" style="mso-cellspacing:1.5pt">
 <tbody><tr>
  <td width="20%" style="width:20.0%;padding:.75pt .75pt .75pt .75pt">
  <p class="MsoNormal"><tt><span style="font-size:10.0pt;font-family:&quot;Courier New&quot;">SIGINT
  (2)</span></tt></p>
  </td>
  <td width="477" style="width:357.75pt;padding:.75pt .75pt .75pt .75pt">
  <p class="MsoNormal">(<i>interrupt</i>) "prekid", može ga se poslati programu sa
	<span lang="hr"> <tt><b><span style="font-size:10.0pt;font-family:&quot;Courier New&quot;">Ctrl-C</span></b></tt></span></p>
  </td>
 </tr>
 <tr>
  <td width="140" style="width:105.0pt;padding:.75pt .75pt .75pt .75pt">
  <p class="MsoNormal"><tt><span style="font-size:10.0pt;font-family:&quot;Courier New&quot;">SIGQUIT
  (3)</span></tt></p>
  </td>
  <td width="477" style="width:357.75pt;padding:.75pt .75pt .75pt .75pt">
  <p class="MsoNormal">(<i>quit</i>) "završi (zbog nekih problema) može ga se 
	poslati programu sa <tt><b>
	<span style="font-size: 10.0pt; font-family: Courier New">Ctrl+\</span></b></tt><span lang="hr"> 
	(na nekim HR tipkovnicama sa </span><tt><b>
	<span style="font-size: 10.0pt; font-family: Courier New">Ctrl+Ž</span></b></tt><span lang="hr">)</span></p>
  </td>
 </tr>
 <tr>
  <td width="140" style="width:105.0pt;padding:.75pt .75pt .75pt .75pt">
  <p class="MsoNormal"><tt><span style="font-size:10.0pt;font-family:&quot;Courier New&quot;">SIGALRM
  (14)</span></tt></p>
  </td>
  <td width="477" style="width:357.75pt;padding:.75pt .75pt .75pt .75pt">
  <p class="MsoNormal">(<i>alarm</i>) koristi se prilikom korištenja funkcije 
	sleep</p>
  </td>
 </tr>
	<tr>
  <td width="140" style="width:105.0pt;padding:.75pt .75pt .75pt .75pt">
  <p class="MsoNormal"><tt><span style="font-size:10.0pt;font-family:&quot;Courier New&quot;">SIGTERM
  (15)</span></tt></p>
  </td>
  <td width="477" style="width:357.75pt;padding:.75pt .75pt .75pt .75pt">
  <p class="MsoNormal">(<i>terminate</i>) traži se od procesa da završi s radom 
	(na redoviti način)</p>
  </td>
 </tr>
 <tr>
  <td width="140" style="width:105.0pt;padding:.75pt .75pt .75pt .75pt">
  <p class="MsoNormal"><tt><span style="font-size:10.0pt;font-family:&quot;Courier New&quot;">
	SIGKILL (9)</span></tt></p>
  </td>
  <td width="477" style="width:357.75pt;padding:.75pt .75pt .75pt .75pt">
  <p class="MsoNormal">(<i>kill</i>) traži se od operacijskog sustava da prekine 
	navedeni proces kome se signal šalje</p>
  </td>
 </tr>
 </tbody></table>

</div>

</span>

<p><span lang="hr">Simbolička imena signala nalaze se u biblioteci <tt><span style="font-size:10.0pt;
font-family:&quot;Courier New&quot;">
<a href="http://www.opengroup.org/onlinepubs/009695399/basedefs/signal.h.html">signal.h</a></span></tt>.</span></p>
<p>U nastavku su prikazane "starije" i jednostavnije funkcije za rad sa 
signalima (upravo zato jer su jednostavnije). Međutim, pri "ozbiljnom" 
korištenju signala treba razmotriti korištenje modernija sucelja (sigaction, 
pthread_kill, pthread_sigmask).<br>
&nbsp;</p><span lang="hr">
<h3>Funkcija <i>
<a href="http://pubs.opengroup.org/onlinepubs/9699919799/functions/sighold.html">
sigset</a></i>(<i> signal</i>, <i>obrada_signala </i>)</h3>

<p>Funkcija definira što ce se zbiti prilikom primitka određenog signala 
(maskira signal). Argument <i>signal</i> je broj signala (npr. SIGINT). Drugi 
argument je kazaljka na funkciju i može biti:</p>
<ul type="disc">
 <li class="MsoNormal" style="mso-margin-top-alt:auto;mso-margin-bottom-alt:auto;
     mso-list:l0 level1 lfo1;tab-stops:list 36.0pt"><tt>
	<span style="font-size:
     10.0pt;font-family:&quot;Courier New&quot;">SIG_DFL</span> </tt>- (<i>default</i>) 
	pretpostavljeno ponašanje za taj signal (za vecinu signala to znaci 
	uništavanje procesa)</li>
 <li class="MsoNormal" style="mso-margin-top-alt:auto;mso-margin-bottom-alt:auto;
     mso-list:l0 level1 lfo1;tab-stops:list 36.0pt"><tt><span style="font-size:
     10.0pt;font-family:&quot;Courier New&quot;">SIG_IGN </span></tt>- (<i>ignore</i>) 
	ignoriranje signala</li>
 <li class="MsoNormal" style="mso-margin-top-alt:auto;mso-margin-bottom-alt:auto;
     mso-list:l0 level1 lfo1;tab-stops:list 36.0pt"><tt><span style="font-size:
     10.0pt;font-family:&quot;Courier New&quot;">SIG_HOLD </span></tt>- (hold) signal se 
	zapamti, ali ne obraduje odmah - obradit ce se onda kada se definicija 
	ponašanja za taj signal promijeni (npr. kasniji poziv sigset)</li>
 <li class="MsoNormal" style="mso-margin-top-alt:auto;mso-margin-bottom-alt:auto;
     mso-list:l0 level1 lfo1;tab-stops:list 36.0pt"><tt><span style="font-size:
     10.0pt;font-family:&quot;Courier New&quot;">obrada_signala</span></tt> - kazaljka<span lang="hr"> na funkciju 
	za obradu signala.</span></li>
</ul>

<p>Funkcija <tt>
<span style="font-size: 10.0pt; font-family: Courier New">sigset</span></tt><span lang="hr"> 
vraća prethodno ponašanje procesa za navedeni signal (ili adresu funkcije kojom 
se signal obrađivao).</span></p></span>
<pre>void obrada_signala( int signal );</pre>
<span lang="hr">
<p>Funkcija za obradu signala treba primiti (minimalno) jedan parametar - broj 
signala, po kojem se u funkciji može odrediti koji je signal uzrok poziva te 
funkcije.</p>
<h3>Funkcije <i>
<a href="http://pubs.opengroup.org/onlinepubs/9699919799/functions/sighold.html">
sighold</a></i>( <i>signal</i> ) i <i>
<a href="http://pubs.opengroup.org/onlinepubs/9699919799/functions/sighold.html">
sigrelse</a></i>( <i>signal</i> )</h3>
<p>Funkcijama <font face="Courier New" size="2">sighold</font> i 
<font face="Courier New" size="2">sigrelse</font><span lang="hr"> može se 
zabraniti, odnosno omogućiti prekidanje nekim signalom.<br>
Primjerice, ako je potrebno jedan dio koda zaštiti od prekidanja nekim signalom, 
taj kod se može ograditi sa&nbsp; <font face="Courier New" size="2">sighold</font> 
i </span><font face="Courier New" size="2">sigrelse</font><span lang="hr">. 
Takoder, ako je u funkciji obrade signala potrebno ponovno dozvoliti prekidanje 
i unutar te funkcije, opet se mogu koristiti te funkcije.</span></p>
<h3><span lang="hr">Funkcija <i>
<a href="http://pubs.opengroup.org/onlinepubs/9699919799/functions/kill.html">
kill</a></i>( <i>pid</i>, <i>signal</i> )</span></h3>
<p><span lang="hr">Funkcijom kill šalje se signal signal procesu s 
identifikacijskim brojem <i>pid</i>. <i>pid</i> procesa se može vidjeti i 
naredbom <i>ps</i>.<br>
U ljusci postoji istoimena naredba <i>kill</i> -<i>signal</i> <i>pid</i> koja 
radi isto (šalje signal procesu). Ukoliko treba ubiti neki proces može se to 
učiniti naredbom <i>kill -SIGKILL pid (ili kill -9 pid)</i>.</span></p>
<h3><span lang="hr">Funkcija <i>
<a href="http://pubs.opengroup.org/onlinepubs/9699919799/functions/pause.html">
pause</a></i>()</span></h3>
<p><span lang="hr">Funkcija zaustavlja rad procesa dok se njemu ne pošalje bilo 
koji signal. Po primitku signala, najprije se obrađuje taj signal, a potom 
nastavlja s programom koji slijedi iza pause.</span></p>
<h3><span lang="hr">Funkcija <i>
<a href="http://pubs.opengroup.org/onlinepubs/9699919799/functions/alarm.html">
alarm</a></i>(<i> t </i>)</span></h3>
<p><span lang="hr">Funkcija <i>alarm(t)</i> programira alarm koji će nakon <i>t</i> 
sekundi procesu poslati signal SIGALRM. Ako se alarm pozove prije nego li se 
prethodno postavljeni alarm aktivirao, prethodni se poništava (prepisuje se 
novim). Ako je <i>t=0</i>, prethodno postavljeni alarm (ako je bilo takvog) se 
poništava.</span></p>
<h3><span lang="hr">Funkcija
<a href="http://pubs.opengroup.org/onlinepubs/9699919799/functions/sleep.html">
sleep</a>( t )</span></h3>
<p><span lang="hr">Namjena funkcije <i>sleep(t)</i> je odgoditi izvođenje 
programa za <i>t</i> sekundi. Medutim, funkcija će biti prekinuta bilo kojim 
signalom te, nakon obrade pristiglog signala, program nastavlja nakon poziva <i>
sleep</i> (i odgoda će u tom slučaju biti kraća), a povratna vrijednost će biti 
broj "neprospavanih" sekundi.<br>
Primjerice, ako se 5 sekundi nakon poziva <i>sleep</i>(100) procesu pošalje neki 
signal (koji se brzo obradi), program će nastaviti s izvođenjem instrukcija 
nakon funkcije <i>sleep</i> već nakon tih 5 sekundi, tj. neće spavati još 95 
nakon obrade signala! Međutim, funkcija <i>sleep</i> će vratiti vrijednost 95 pa 
se ta vrijednost može iskoristiti za dodatnu odgodu:</span></p>
<pre style="font-size: 10.0pt; font-family: Courier New; margin-left: 0cm; margin-right: 0cm; margin-top: 0cm; margin-bottom: .0001pt">a = sleep(100);</pre>
<pre style="font-size: 10.0pt; font-family: Courier New; margin-left: 0cm; margin-right: 0cm; margin-top: 0cm; margin-bottom: .0001pt">while( (a = sleep( a )) &gt; 0 );</pre>
<p><span lang="hr">Odgoda s mogučnošću veće preciznosti je funkcija <i>
<a href="http://pubs.opengroup.org/onlinepubs/9699919799/functions/nanosleep.html">
nanosleep</a>(t)</i>. Postoji i funkcija <i>usleep(us)</i> (mikrosekunde), ali 
se njeno korištenje ne preporuča (smatra se zastarjelom).</span></p>
<span lang="hr">

<p>Umjesto funkcije <font face="Courier New" size="2">sigset</font> može se 
koristiti i naprednija funckija <font face="Courier New" size="2">
<a href="http://www.opengroup.org/onlinepubs/007908799/xsh/sigaction.html">
sigaction</a></font>. Opis te funkcije dan je i kratkim <a href="http://zemris.fer.hr/predmeti/os/pripreme/upute/sigaction.c">
primjerom</a>. </p>
</span>
<p><span lang="hr">Kostur programa koji poziva zadanu funkciju prilikom primitka 
signala SIGINT dan je sljedecim kodom:</span></p>

<pre style="font-size: 10.0pt; font-family: Courier New; margin-left: 0cm; margin-right: 0cm; margin-top: 0cm; margin-bottom: .0001pt">#include &lt;stdio.h&gt;</pre>
<pre style="font-size: 10.0pt; font-family: Courier New; margin-left: 0cm; margin-right: 0cm; margin-top: 0cm; margin-bottom: .0001pt">#include &lt;signal.h&gt;</pre>
<pre style="font-size: 10.0pt; font-family: Courier New; margin-left: 0cm; margin-right: 0cm; margin-top: 0cm; margin-bottom: .0001pt">&nbsp;</pre>
<pre style="font-size: 10.0pt; font-family: Courier New; margin-left: 0cm; margin-right: 0cm; margin-top: 0cm; margin-bottom: .0001pt">void prekidna_rutina(int sig)
{
<span style="mso-spacerun: yes">&nbsp;&nbsp; </span>/* <i>obrada prekida</i> */</pre>
<pre style="font-size: 10.0pt; font-family: Courier New; margin-left: 0cm; margin-right: 0cm; margin-top: 0cm; margin-bottom: .0001pt">}</pre>
<pre style="font-size: 10.0pt; font-family: Courier New; margin-left: 0cm; margin-right: 0cm; margin-top: 0cm; margin-bottom: .0001pt"></pre>
<pre style="font-size: 10.0pt; font-family: Courier New; margin-left: 0cm; margin-right: 0cm; margin-top: 0cm; margin-bottom: .0001pt">int main (void)</pre>
<pre style="font-size: 10.0pt; font-family: Courier New; margin-left: 0cm; margin-right: 0cm; margin-top: 0cm; margin-bottom: .0001pt">{</pre>
<pre style="font-size: 10.0pt; font-family: Courier New; margin-left: 0cm; margin-right: 0cm; margin-top: 0cm; margin-bottom: .0001pt"><span style="mso-spacerun: yes">&nbsp;&nbsp; </span>sigset (SIGTSTP, prekidna_rutina);</pre>
<pre style="font-size: 10.0pt; font-family: Courier New; margin-left: 0cm; margin-right: 0cm; margin-top: 0cm; margin-bottom: .0001pt">&nbsp;</pre>
<pre style="font-size: 10.0pt; font-family: Courier New; margin-left: 0cm; margin-right: 0cm; margin-top: 0cm; margin-bottom: .0001pt">   printf("Poceo osnovni program PID=%d\n", getpid());
</pre>
<pre style="font-size: 10.0pt; font-family: Courier New; margin-left: 0cm; margin-right: 0cm; margin-top: 0cm; margin-bottom: .0001pt">&nbsp;</pre>
<pre style="font-size: 10.0pt; font-family: Courier New; margin-left: 0cm; margin-right: 0cm; margin-top: 0cm; margin-bottom: .0001pt"><span style="mso-spacerun: yes">&nbsp;&nbsp; </span>/* <i>troši vrijeme da se ima šta prekinuti - 10 s</i> */</pre>
<pre style="font-size: 10.0pt; font-family: Courier New; margin-left: 0cm; margin-right: 0cm; margin-top: 0cm; margin-bottom: .0001pt">&nbsp;</pre>
<pre style="font-size: 10.0pt; font-family: Courier New; margin-left: 0cm; margin-right: 0cm; margin-top: 0cm; margin-bottom: .0001pt"><span style="mso-spacerun: yes">&nbsp;&nbsp; </span>printf ("Zavrsio osnovni program\n");</pre>
<pre style="font-size: 10.0pt; font-family: Courier New; margin-left: 0cm; margin-right: 0cm; margin-top: 0cm; margin-bottom: .0001pt"></pre>
<pre style="font-size: 10.0pt; font-family: Courier New; margin-left: 0cm; margin-right: 0cm; margin-top: 0cm; margin-bottom: .0001pt"><span style="mso-spacerun: yes">&nbsp;&nbsp; </span>return 0;</pre>
<pre style="font-size: 10.0pt; font-family: Courier New; margin-left: 0cm; margin-right: 0cm; margin-top: 0cm; margin-bottom: .0001pt">}</pre>
</span></div>


<!-- saved from url=(0050)http://zemris.fer.hr/predmeti/os/pripreme/z1a.html -->

<h2>Vježba 1: Signali</h2>
<h3>Zadatak</h3>

<span style="color: rgb(0, 0, 0); font-family: &#39;Times New Roman&#39;; font-size: medium; font-style: normal; font-variant: normal; font-weight: normal; letter-spacing: normal; line-height: normal; orphans: auto; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: auto; word-spacing: 0px; -webkit-text-stroke-width: 0px; display: inline !important; float: none;">
Računati proste brojeve te preko signala periodički ispisivati status. Koristiti<span class="Apple-converted-space">&nbsp;</span></span><i style="color: rgb(0, 0, 0); font-family: &#39;Times New Roman&#39;; font-size: medium; font-variant: normal; font-weight: normal; letter-spacing: normal; line-height: normal; orphans: auto; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: auto; word-spacing: 0px; -webkit-text-stroke-width: 0px;">setitimer</i><span style="color: rgb(0, 0, 0); font-family: &#39;Times New Roman&#39;; font-size: medium; font-style: normal; font-variant: normal; font-weight: normal; letter-spacing: normal; line-height: normal; orphans: auto; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: auto; word-spacing: 0px; -webkit-text-stroke-width: 0px; display: inline !important; float: none;"><span class="Apple-converted-space">&nbsp;</span>sučelje 
za periodički alarm (vidjeti Primjer periodičke obrade pri dnu stranice). Na 
signal SIGINT privremeno zaustaviti rad na idućim brojevima (programski 
ostvariti zaustavljanje), odnosno, nastaviti s radom ako je program prethodno 
bio zaustavljen. Na signal SIGTERM ispisati zadnji broj koji se provjerava (ili 
će biti idući) i završiti s radom.</span><p style="color: rgb(0, 0, 0); font-family: &#39;Times New Roman&#39;; font-size: medium; font-style: normal; font-variant: normal; font-weight: normal; letter-spacing: normal; line-height: normal; orphans: auto; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: auto; word-spacing: 0px; -webkit-text-stroke-width: 0px;">
<a name="skica">Skica rješenja</a>:</p>
<pre style="color: rgb(0, 0, 0); font-style: normal; font-variant: normal; font-weight: normal; letter-spacing: normal; line-height: normal; orphans: auto; text-align: start; text-indent: 0px; text-transform: none; widows: auto; word-spacing: 0px; -webkit-text-stroke-width: 0px;">pauza = 0;
broj = 1000000001;
zadnji = 1000000001;

periodicki_ispis () {
   ispisi ( zadnji );
}

postavi_pauzu () {
   pauza = 1 - pauza;
}

prekini () {
   ispisi ( zadnji );
   izadji_iz_programa ();
}

glavna_funkcija () {
   povezi_signale_s_funkcijama; // na signal SIGTERM pozovi funkciju prekini()
   postavi_periodicki_alarm;    // svakih 5 sekundi pozovi funkciju periodicki_ispis();

   ponavljaj {
      ako je ( prost ( broj ) == DA )
         zadnji = broj;
      broj++;
      dok je ( pauza == 1 )
         pauziraj ();
   }
}

/* sa kill -SIGINT/SIGTERM/SIGSTOP/SIGCONT pid ispitati rad */
</pre>
<span style="color: rgb(0, 0, 0); font-family: &#39;Times New Roman&#39;; font-size: medium; font-style: normal; font-variant: normal; font-weight: normal; letter-spacing: normal; line-height: normal; orphans: auto; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: auto; word-spacing: 0px; -webkit-text-stroke-width: 0px; display: inline !important; float: none;">
Provjera je li broj prost može se obaviti jednostavnim kodom, npr. prema:</span><pre style="color: rgb(0, 0, 0); font-style: normal; font-variant: normal; font-weight: normal; letter-spacing: normal; line-height: normal; orphans: auto; text-align: start; text-indent: 0px; text-transform: none; widows: auto; word-spacing: 0px; -webkit-text-stroke-width: 0px;">int prost ( unsigned long n ) {
	unsigned long i, max;

	if ( ( n &amp; 1 ) == 0 ) /* je li paran? */
		return 0;

	max = sqrt ( n );
	for ( i = 3; i &lt;= max; i += 2 )
		if ( ( n % i ) == 0 )
			return 0;

	return 1; /* broj je prost! */
}
</pre>
<span style="color: rgb(0, 0, 0); font-family: &#39;Times New Roman&#39;; font-size: medium; font-style: normal; font-variant: normal; font-weight: normal; letter-spacing: normal; line-height: normal; orphans: auto; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: auto; word-spacing: 0px; -webkit-text-stroke-width: 0px; display: inline !important; float: none;">
Primjer kako bi trebao izgledati ispis programa (ako se izvorna datoteka zove 
lab1.c):</span><pre style="color: rgb(0, 0, 0); font-style: normal; font-variant: normal; font-weight: normal; letter-spacing: normal; line-height: normal; orphans: auto; text-align: start; text-indent: 0px; text-transform: none; widows: auto; word-spacing: 0px; -webkit-text-stroke-width: 0px;">$ gcc lab1.c -lm -o lab1
$ ./lab1
zadnji prosti broj = 1000139111
zadnji prosti broj = 1000279801
zadnji prosti broj = 1000420261
^Czadnji prosti broj = 1000478719    (stisnut Ctrl+C)
zadnji prosti broj = 1000478719
zadnji prosti broj = 1000478719      (stisnut [Ctrl]+[\] tj. [Ctrl]+[Ž])
^\Quit (core dumped)
$
<span style="color: rgb(0, 0, 0); font-family: &#39;Times New Roman&#39;; font-size: medium; font-style: normal; font-variant: normal; font-weight: normal; letter-spacing: normal; line-height: normal; orphans: auto; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: auto; word-spacing: 0px; -webkit-text-stroke-width: 0px; display: inline !important; float: none;">(Tekst u zagradama ne ispisuje program već se samo opisuju korisnikove radnje.)</span></pre>
<span style="font-family: Times New Roman; font-size: medium; letter-spacing: normal; font-weight: 700">
Primjer periodičke obrade</span><p>
<span style="color: rgb(0, 0, 0); font-family: &#39;Times New Roman&#39;; font-size: medium; font-style: normal; font-variant: normal; font-weight: normal; letter-spacing: normal; line-height: normal; orphans: auto; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: auto; word-spacing: 0px; -webkit-text-stroke-width: 0px; display: inline !important; float: none;">
Mnoge operacije na UNIX sustavima se oslanjaju na signale. Primjerice, jedan od 
načina periodičke obrade može se ostvariti korištenjem signala, ne izravno već 
korištenjem sučelja koje periodički šalje signal procesu, a na koji se može 
pozvati potrebna funkcija.</span></p>
<p style="color: rgb(0, 0, 0); font-family: &#39;Times New Roman&#39;; font-size: medium; font-style: normal; font-variant: normal; font-weight: normal; letter-spacing: normal; line-height: normal; orphans: auto; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows: auto; word-spacing: 0px; -webkit-text-stroke-width: 0px;">
Idući primjer,<span class="Apple-converted-space">&nbsp;</span><a href="http://www.zemris.fer.hr/~leonardo/os/phy/labosi/upute/lab1/itimer_primjer.c">itimer_primjer.c</a>, 
prikazuje takav program.</p>
<pre style="color: rgb(0, 0, 0); font-style: normal; font-variant: normal; font-weight: normal; letter-spacing: normal; line-height: normal; orphans: auto; text-align: start; text-indent: 0px; text-transform: none; widows: auto; word-spacing: 0px; -webkit-text-stroke-width: 0px;">#include &lt;stdio.h&gt;
#include &lt;signal.h&gt;
#include &lt;unistd.h&gt;
#include &lt;sys/time.h&gt;

void periodicki_posao ( int sig )
{
	printf ( "Radim periodicki posao\n" );
}

int main ()
{
	struct itimerval t;

	/* povezivanje obrade signala SIGALRM sa funkcijom "periodicki_posao" */
	sigset ( SIGALRM, periodicki_posao );

	/* definiranje periodičkog slanja signala */
	/* prvi puta nakon: */
	t.it_value.tv_sec = 0;
	t.it_value.tv_usec = 500000;
	/* nakon prvog puta, periodicki sa periodom: */
	t.it_interval.tv_sec = 0;
	t.it_interval.tv_usec = 500000;

	/* pokretanje sata s pridruženim slanjem signala prema "t" */
	setitimer ( ITIMER_REAL, &amp;t, NULL );

	while (1)
		pause (); /* pauzira do primitka bilo kojeg signala */

	return 0;
}

/* prevodjenje i pokretanje:
 * $ gcc itimer_primjer.c -o itimer_primjer
 * $ ./itimer_primjer
 * Radim periodicki posao
 * Radim periodicki posao
 * Radim periodicki posao
 * ...
 * ^C
 * (Ctrl+C prekida izvodjenje)
 *
 * isprobati pokrenuti te s naredbom kill mu poslati signale:
 * - SIGINT, SIGTERM, SIGKILL, SIGSTOP, SIGCONT
 *
 * npr. nakon pokretanja, u drugoj konzoli napraviti:
 * $ ps -a
 * PID  TTY          TIME CMD
 * 3232 pts/0    00:00:00 itimer_primjer
 * 3233 pts/6    00:00:00 ps
 * $ kill -SIGTERM 3232
 * u prvoj konzoli će program biti prekinut s porukom "Terminated"
 */
</pre>


<!-- saved from url=(0050)http://zemris.fer.hr/predmeti/os/pripreme/z1b.html -->

<h2>Vježba 1: Prekidi i signali</h2>

<p>UNIX ne dozvoljava pojedinom korisniku izravno korištenje prekida procesora.
Stoga prekide treba simulirati koristeći <i>signale</i> koje jezgra operacijskog
sustava šalje procesima.</p>

<h3>Zadatak</h3>

<div class="Section1">

Napisati dva programa:
<ul>
	<li><font face="Courier New" size="2">obrada</font> - program koji omogućava 
	obradu prekida s više razina/prioriteta (simulira ponašanje sustava opisanog 
	u 3. poglavlju i to bez sklopa za prihvat prekida)</li>
	<li><font face="Courier New" size="2">generator_prekida</font> - program koji generira signale i šalje ih prvom procesu </li>
</ul>
<p>Svaki program pokrenuti u svojoj ljusci.</p>
<p>Struktura prekidne rutine dana je sljedećim pseudokodom:</p>
<div style="border-style: solid; border-width: 1px; padding-left: 4px; padding-right: 4px; padding-top: 1px; padding-bottom: 1px">
<pre>prekidna_rutina<span style="mso-spacerun: yes">&nbsp; </span>/* <i>pokreće se pojavom signala uz zabranu daljih prekida</i> */
{<span style="mso-spacerun: yes">
&nbsp;&nbsp; </span>odredi uzrok prekida, tj. indeks <b>i;
</b>   OZNAKA_ČEKANJA[<b>i</b>] = 1;</pre>
<pre>   ponavljaj {
      /* odredi signal najveceg prioriteta koji ceka na obradu */
      x = 0;<span style="mso-spacerun: yes">
&nbsp;&nbsp;    za j = </span>TEKUćI_PRIORITET<span style="mso-spacerun: yes"> + 1 do N radi {
</span>         ako je (OZNAKA_ČEKANJA[<b>j</b>]&lt;&gt;0) tada {
            x = j;
         }
      }</pre>
<pre>      /* ako postoji signal koji ceka i prioritetniji je od trenutnog posla, idi u obradu */
      ako je (x &gt; 0) tada {<span style="mso-spacerun: yes">
      &nbsp;&nbsp;&nbsp;</span>OZNAKA_ČEKANJA[<b>x</b>] = 0;<span style="mso-spacerun: yes">
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;    </span>PRIORITET[<b>x</b>] = TEKUćI_PRIORITET;<span style="mso-spacerun: yes">
      &nbsp;&nbsp;&nbsp;</span>TEKUćI_PRIORITET = <b>x;</b><span style="mso-spacerun: yes">
      &nbsp;&nbsp;&nbsp;</span>omogući prekidanje;<span style="mso-spacerun: yes">
      &nbsp;&nbsp;&nbsp;</span>obrada_prekida(<b>x</b>);<span style="mso-spacerun: yes">
      &nbsp;&nbsp;&nbsp;</span>zabrani prekidanje;<span style="mso-spacerun: yes">
      &nbsp;&nbsp;&nbsp;</span>TEKUćI_PRIORITET = PRIORITET[<b>x</b>];
      }</pre>
<pre>   } dok je (x &gt; 0);
} </pre>

</div>

</div>
<span class="Apple-style-span" style="border-collapse: separate; color: rgb(0, 0, 0); font-family: &#39;Times New Roman&#39;; font-style: normal; font-variant: normal; font-weight: normal; letter-spacing: normal; line-height: normal; orphans: 2; text-align: -webkit-auto; text-indent: 0px; text-transform: none; white-space: normal; widows: 2; word-spacing: 0px; -webkit-border-horizontal-spacing: 0px; -webkit-border-vertical-spacing: 0px; -webkit-text-decorations-in-effect: none; -webkit-text-size-adjust: auto; -webkit-text-stroke-width: 0px; font-size: medium; ">
<div class="Section1" style="page: Section1; ">
	<h2>UPUTA</h2>
	<p style="font-size: 12pt; font-family: &#39;Times New Roman&#39;; ">Sklopovski 
	prekid u jednoj razini simulira se slanjem određene vrste signala. Nakon 
	toga će se prekinuti izvođenje programa, zabraniti dalje prekidanje, i 
	pozvati funkcija za obradu signala koja simulira prekidnu rutinu.</p>
	<p style="font-size: 12pt; font-family: &#39;Times New Roman&#39;; ">Osim izravno 
	preko tipkovnice, proces može dobiti signal do drugog procesa (funkcija<span class="Apple-converted-space">&nbsp;</span><font size="2" face="Courier New">kill(pid,sig)</font>). 
	Također, iz komandne linije se naredbom<span class="Apple-converted-space">&nbsp;</span><font size="2" face="Courier New"><a href="http://www.opengroup.org/onlinepubs/007908799/xcu/kill.html">kill</a></font><span class="Apple-converted-space">&nbsp;</span>može 
	poslati signal nekom od procesa (npr.<span class="Apple-converted-space">&nbsp;</span><font face="Courier New" size="2">kill 
	-SIGINT 12345</font>).</p>
	<p style="font-size: 12pt; font-family: &#39;Times New Roman&#39;; ">Na početku 
	prekidne rutine prvo treba zabraniti daljnje prekidanje. Kako se koristi 
	više signala, 
	na osnovu signala koji je uzrokovao prekid treba odrediti razinu prioriteta 
	prekida<span class="Apple-converted-space">&nbsp;</span><i>i</i>. Prekidna rutina 
	mora biti funkcija s jednim cjelobrojnim parametrom i mora biti najavljena u 
	glavnom programu za svaki signal koji se prihvaća naredbom:</p>
	<pre style="margin-top: 0cm; margin-right: 0cm; margin-left: 0cm; margin-bottom: 0.0001pt; font-size: 10pt; font-family: &#39;Courier New&#39;; ">sigset (<i>SIGNAL</i>, prekidna_rutina);</pre>
	<p style="font-size: 12pt; font-family: &#39;Times New Roman&#39;; ">Program treba 
	moći prihvatiti i obraditi pet različitih signala 
	(<a href="http://www.opengroup.org/onlinepubs/009695399/basedefs/signal.h.html">odabrati 
	iz skupa signala</a>) s time da prekid SIGINT treba biti najveće razine.&nbsp; 
	Razine prioriteta se kreću od 1 do 5 s time da veći broj označava veći 
	prioritet.</p>
	<p style="font-size: 12pt; font-family: &#39;Times New Roman&#39;; ">Zabrana prekida 
	signalom<span class="Apple-converted-space">&nbsp;</span><tt><span style="font-size: 10pt; font-family: &#39;Courier New&#39;; "><i>SIGNAL<span class="Apple-converted-space">&nbsp;</span></i></span></tt>simulira 
	se naredbom<span class="Apple-converted-space">&nbsp;</span><tt><span style="font-size: 10pt; font-family: &#39;Courier New&#39;; ">sighold(<i>SIGNAL</i>)</span></tt>, 
	a omogućavanje 
	prekida simulira se naredbom:<span class="Apple-converted-space">&nbsp;</span><tt><span style="font-size: 10pt; font-family: &#39;Courier New&#39;; ">sigrelse(<i>SIGNAL</i>);</span></tt></p>
	<p style="font-size: 12pt; font-family: &#39;Times New Roman&#39;; ">Budući da<font size="3">
	se ovdje ista funkcija koristi za obradu više prekida funkcije<span class="Apple-converted-space">&nbsp;</span></font><tt><span style="font-size: 10pt; font-family: &#39;Courier New&#39;; ">sighold<span class="Apple-converted-space">&nbsp;</span></span></tt><font size="3">i<span class="Apple-converted-space">&nbsp;</span></font><tt><span style="font-size: 10pt; font-family: &#39;Courier New&#39;; ">sigrelse<span class="Apple-converted-space">&nbsp;</span></span></tt><font size="3">treba 
	pozvati za svaki od signala (više uzastopnih poziva)! Zbog toga je zgodno te 
	pozive grupirati u dvije funkcije:<span class="Apple-converted-space">&nbsp;</span></font>zabrani_prekidanje() 
	i dozvoli_prekidanje(), kao u kosturu rješenja.</p>
	<p style="font-size: 12pt; font-family: &#39;Times New Roman&#39;; ">Obrada prekida 
	ne mora ništa korisno raditi, već samo treba trajati neko vrijeme. Umjesto 
	dugih petlji, može poslužiti petlja s naredbom<span class="Apple-converted-space">&nbsp;</span><i>sleep(1)</i>.</p>
	<p style="font-size: 12pt; font-family: &#39;Times New Roman&#39;; ">Kostur rješenja 
	programa za obradu prekida dan je sljedećim kodom:</p>
	<pre style="margin-top: 0cm; margin-right: 0cm; margin-left: 0cm; margin-bottom: 0.0001pt; font-size: 10pt; font-family: &#39;Courier New&#39;; ">#include &lt;stdio.h&gt;</pre>
	<pre style="margin-top: 0cm; margin-right: 0cm; margin-left: 0cm; margin-bottom: 0.0001pt; font-size: 10pt; font-family: &#39;Courier New&#39;; ">#include &lt;signal.h&gt;</pre>
	<pre style="margin-top: 0cm; margin-right: 0cm; margin-left: 0cm; margin-bottom: 0.0001pt; font-size: 10pt; font-family: &#39;Courier New&#39;; ">&nbsp;</pre>
	<pre style="margin-top: 0cm; margin-right: 0cm; margin-left: 0cm; margin-bottom: 0.0001pt; font-size: 10pt; font-family: &#39;Courier New&#39;; ">#define N 6&nbsp;&nbsp;&nbsp; /* <i>broj razina proriteta</i> */</pre>
	<pre style="margin-top: 0cm; margin-right: 0cm; margin-left: 0cm; margin-bottom: 0.0001pt; font-size: 10pt; font-family: &#39;Courier New&#39;; ">&nbsp;</pre>
	<pre style="margin-top: 0cm; margin-right: 0cm; margin-left: 0cm; margin-bottom: 0.0001pt; font-size: 10pt; font-family: &#39;Courier New&#39;; ">int OZNAKA_CEKANJA[N];</pre>
	<pre style="margin-top: 0cm; margin-right: 0cm; margin-left: 0cm; margin-bottom: 0.0001pt; font-size: 10pt; font-family: &#39;Courier New&#39;; ">int PRIORITET[N];</pre>
	<pre style="margin-top: 0cm; margin-right: 0cm; margin-left: 0cm; margin-bottom: 0.0001pt; font-size: 10pt; font-family: &#39;Courier New&#39;; ">int TEKUCI_PRIORITET;</pre>
	<pre style="margin-top: 0cm; margin-right: 0cm; margin-left: 0cm; margin-bottom: 0.0001pt; font-size: 10pt; font-family: &#39;Courier New&#39;; ">&nbsp;</pre>
	<pre style="margin-top: 0cm; margin-right: 0cm; margin-left: 0cm; margin-bottom: 0.0001pt; font-size: 10pt; font-family: &#39;Courier New&#39;; ">&nbsp;</pre>
	<pre style="margin-top: 0cm; margin-right: 0cm; margin-left: 0cm; margin-bottom: 0.0001pt; font-size: 10pt; font-family: &#39;Courier New&#39;; ">int sig[]={SIGUSR1, SIGUSR2, ..., SIGINT};</pre>
	<pre style="margin-top: 0cm; margin-right: 0cm; margin-left: 0cm; margin-bottom: 0.0001pt; font-size: 10pt; font-family: &#39;Courier New&#39;; ">void zabrani_prekidanje(){</pre>
	<pre style="margin-top: 0cm; margin-right: 0cm; margin-left: 0cm; margin-bottom: 0.0001pt; font-size: 10pt; font-family: &#39;Courier New&#39;; ">   int i;</pre>
	<pre style="margin-top: 0cm; margin-right: 0cm; margin-left: 0cm; margin-bottom: 0.0001pt; font-size: 10pt; font-family: &#39;Courier New&#39;; ">   for(i=0; i&lt;5; i++)</pre>
	<pre style="margin-top: 0cm; margin-right: 0cm; margin-left: 0cm; margin-bottom: 0.0001pt; font-size: 10pt; font-family: &#39;Courier New&#39;; ">      sighold(sig[i]);</pre>
	<pre style="margin-top: 0cm; margin-right: 0cm; margin-left: 0cm; margin-bottom: 0.0001pt; font-size: 10pt; font-family: &#39;Courier New&#39;; ">}</pre>
	<pre style="margin-top: 0cm; margin-right: 0cm; margin-left: 0cm; margin-bottom: 0.0001pt; font-size: 10pt; font-family: &#39;Courier New&#39;; ">void dozvoli_prekidanje(){</pre>
	<pre style="margin-top: 0cm; margin-right: 0cm; margin-left: 0cm; margin-bottom: 0.0001pt; font-size: 10pt; font-family: &#39;Courier New&#39;; ">   int i;</pre>
	<pre style="margin-top: 0cm; margin-right: 0cm; margin-left: 0cm; margin-bottom: 0.0001pt; font-size: 10pt; font-family: &#39;Courier New&#39;; ">   for(i=0; i&lt;5; i++)</pre>
	<pre style="margin-top: 0cm; margin-right: 0cm; margin-left: 0cm; margin-bottom: 0.0001pt; font-size: 10pt; font-family: &#39;Courier New&#39;; ">      sigrelse(sig[i]);</pre>
	<pre style="margin-top: 0cm; margin-right: 0cm; margin-left: 0cm; margin-bottom: 0.0001pt; font-size: 10pt; font-family: &#39;Courier New&#39;; ">}</pre>
	<pre style="margin-top: 0cm; margin-right: 0cm; margin-left: 0cm; margin-bottom: 0.0001pt; font-size: 10pt; font-family: &#39;Courier New&#39;; ">&nbsp;</pre>
	<pre style="margin-top: 0cm; margin-right: 0cm; margin-left: 0cm; margin-bottom: 0.0001pt; font-size: 10pt; font-family: &#39;Courier New&#39;; ">void obrada_signala(int i){
&nbsp;&nbsp; /* <i>obrada se simulira trošenjem vremena,</i></pre>
	<pre style="margin-top: 0cm; margin-right: 0cm; margin-left: 0cm; margin-bottom: 0.0001pt; font-size: 10pt; font-family: &#39;Courier New&#39;; "><i>      obrada traje 5 sekundi, ispis treba biti svake sekunde</i> */</pre>
	<pre style="margin-top: 0cm; margin-right: 0cm; margin-left: 0cm; margin-bottom: 0.0001pt; font-size: 10pt; font-family: &#39;Courier New&#39;; ">}
</pre>
	<pre style="margin-top: 0cm; margin-right: 0cm; margin-left: 0cm; margin-bottom: 0.0001pt; font-size: 10pt; font-family: &#39;Courier New&#39;; ">void prekidna_rutina(int sig){
   int n=-1;</pre>
	<pre style="margin-top: 0cm; margin-right: 0cm; margin-left: 0cm; margin-bottom: 0.0001pt; font-size: 10pt; font-family: &#39;Courier New&#39;; "><font color="#FF0000">   zabrani_prekidanje();
</font>   switch(sig){
      case SIGUSR1: </pre>
	<pre style="margin-top: 0cm; margin-right: 0cm; margin-left: 0cm; margin-bottom: 0.0001pt; font-size: 10pt; font-family: &#39;Courier New&#39;; ">         n=1; 
         printf("- X - - - -\n");
         break;
      case SIGUSR2: </pre>
	<pre style="margin-top: 0cm; margin-right: 0cm; margin-left: 0cm; margin-bottom: 0.0001pt; font-size: 10pt; font-family: &#39;Courier New&#39;; ">         n=2; 
         printf("- - X - - -\n");
         break;
      ...</pre>
	<pre style="margin-top: 0cm; margin-right: 0cm; margin-left: 0cm; margin-bottom: 0.0001pt; font-size: 10pt; font-family: &#39;Courier New&#39;; ">   }</pre>
	<pre style="margin-top: 0cm; margin-right: 0cm; margin-left: 0cm; margin-bottom: 0.0001pt; font-size: 10pt; font-family: &#39;Courier New&#39;; ">   OZNAKA_CEKANJA[n]=1;
&nbsp;  ponavljaj{</pre>


<span class="Apple-style-span" style="border-collapse: separate; font-family: &#39;Times New Roman&#39;; font-style: normal; font-variant: normal; font-weight: normal; letter-spacing: normal; line-height: normal; orphans: 2; text-align: -webkit-auto; text-indent: 0px; text-transform: none; white-space: normal; widows: 2; word-spacing: 0px; -webkit-border-horizontal-spacing: 0px; -webkit-border-vertical-spacing: 0px; -webkit-text-decorations-in-effect: none; -webkit-text-size-adjust: auto; -webkit-text-stroke-width: 0px; font-size: medium">
	<pre style="margin-top: 0cm; margin-right: 0cm; margin-left: 0cm; margin-bottom: 0.0001pt; font-size: 10pt; font-family: &#39;Courier New&#39;; "><font color="#FF0000">      ...</font></pre>
</span>

<span class="Apple-style-span" style="border-collapse: separate; color: rgb(0, 0, 0); font-family: &#39;Times New Roman&#39;; font-style: normal; font-variant: normal; font-weight: normal; letter-spacing: normal; line-height: normal; orphans: 2; text-align: -webkit-auto; text-indent: 0px; text-transform: none; white-space: normal; widows: 2; word-spacing: 0px; -webkit-border-horizontal-spacing: 0px; -webkit-border-vertical-spacing: 0px; -webkit-text-decorations-in-effect: none; -webkit-text-size-adjust: auto; -webkit-text-stroke-width: 0px; font-size: medium; ">
<span class="Apple-style-span" style="border-collapse: separate; color: rgb(0, 0, 0); font-family: &#39;Times New Roman&#39;; font-style: normal; font-variant: normal; font-weight: normal; letter-spacing: normal; line-height: normal; orphans: 2; text-align: -webkit-auto; text-indent: 0px; text-transform: none; white-space: normal; widows: 2; word-spacing: 0px; -webkit-border-horizontal-spacing: 0px; -webkit-border-vertical-spacing: 0px; -webkit-text-decorations-in-effect: none; -webkit-text-size-adjust: auto; -webkit-text-stroke-width: 0px; font-size: medium; ">
	<pre style="margin-top: 0cm; margin-right: 0cm; margin-left: 0cm; margin-bottom: 0.0001pt; font-size: 10pt; font-family: &#39;Courier New&#39;; "><font color="#FF0000">      dozvoli_prekidanje();</font></pre>
</span>

	<pre style="margin-top: 0cm; margin-right: 0cm; margin-left: 0cm; margin-bottom: 0.0001pt; font-size: 10pt; font-family: &#39;Courier New&#39;; "> &nbsp;    obrada_prekida(n);</pre>
	<pre style="margin-top: 0cm; margin-right: 0cm; margin-left: 0cm; margin-bottom: 0.0001pt; font-size: 10pt; font-family: &#39;Courier New&#39;; "><font color="#FF0000">      zabrani_prekidanje();</font></pre>
	<pre style="margin-top: 0cm; margin-right: 0cm; margin-left: 0cm; margin-bottom: 0.0001pt; font-size: 10pt; font-family: &#39;Courier New&#39;; ">      ...</pre>
	<pre style="margin-top: 0cm; margin-right: 0cm; margin-left: 0cm; margin-bottom: 0.0001pt; font-size: 10pt; font-family: &#39;Courier New&#39;; ">   }</pre>
<span class="Apple-style-span" style="border-collapse: separate; color: rgb(0, 0, 0); font-family: &#39;Times New Roman&#39;; font-style: normal; font-variant: normal; font-weight: normal; letter-spacing: normal; line-height: normal; orphans: 2; text-align: -webkit-auto; text-indent: 0px; text-transform: none; white-space: normal; widows: 2; word-spacing: 0px; -webkit-border-horizontal-spacing: 0px; -webkit-border-vertical-spacing: 0px; -webkit-text-decorations-in-effect: none; -webkit-text-size-adjust: auto; -webkit-text-stroke-width: 0px; font-size: medium; ">
	<pre style="margin-top: 0cm; margin-right: 0cm; margin-left: 0cm; margin-bottom: 0.0001pt; font-size: 10pt; font-family: &#39;Courier New&#39;; "><font color="#FF0000">   dozvoli_prekidanje();</font></pre>
</span>

	<pre style="margin-top: 0cm; margin-right: 0cm; margin-left: 0cm; margin-bottom: 0.0001pt; font-size: 10pt; font-family: &#39;Courier New&#39;; ">}</pre>
	<pre style="margin-top: 0cm; margin-right: 0cm; margin-left: 0cm; margin-bottom: 0.0001pt; font-size: 10pt; font-family: &#39;Courier New&#39;; ">&nbsp;</pre>
	<pre style="margin-top: 0cm; margin-right: 0cm; margin-left: 0cm; margin-bottom: 0.0001pt; font-size: 10pt; font-family: &#39;Courier New&#39;; ">int main ( void )</pre>
	<pre style="margin-top: 0cm; margin-right: 0cm; margin-left: 0cm; margin-bottom: 0.0001pt; font-size: 10pt; font-family: &#39;Courier New&#39;; ">{</pre>
	<pre style="margin-top: 0cm; margin-right: 0cm; margin-left: 0cm; margin-bottom: 0.0001pt; font-size: 10pt; font-family: &#39;Courier New&#39;; ">&nbsp;&nbsp; sigset (SIGUSR1, prekidna_rutina);</pre>
	<pre style="margin-top: 0cm; margin-right: 0cm; margin-left: 0cm; margin-bottom: 0.0001pt; font-size: 10pt; font-family: &#39;Courier New&#39;; ">   ...</pre>
	<pre style="margin-top: 0cm; margin-right: 0cm; margin-left: 0cm; margin-bottom: 0.0001pt; font-size: 10pt; font-family: &#39;Courier New&#39;; ">&nbsp;&nbsp; sigset (SIGINT, prekidna_rutina);</pre>
	<pre style="margin-top: 0cm; margin-right: 0cm; margin-left: 0cm; margin-bottom: 0.0001pt; font-size: 10pt; font-family: &#39;Courier New&#39;; ">&nbsp;</pre>
	<pre style="margin-top: 0cm; margin-right: 0cm; margin-left: 0cm; margin-bottom: 0.0001pt; font-size: 10pt; font-family: &#39;Courier New&#39;; ">   printf("Proces obrade prekida, PID=%ld\n", getpid());
</pre>
	<pre style="margin-top: 0cm; margin-right: 0cm; margin-left: 0cm; margin-bottom: 0.0001pt; font-size: 10pt; font-family: &#39;Courier New&#39;; ">&nbsp;&nbsp; /* <i>troši vrijeme da se ima šta prekinuti - 10 s</i> */</pre>
	<pre style="margin-top: 0cm; margin-right: 0cm; margin-left: 0cm; margin-bottom: 0.0001pt; font-size: 10pt; font-family: &#39;Courier New&#39;; ">&nbsp;</pre>
	<pre style="margin-top: 0cm; margin-right: 0cm; margin-left: 0cm; margin-bottom: 0.0001pt; font-size: 10pt; font-family: &#39;Courier New&#39;; ">&nbsp;&nbsp; printf ("Zavrsio osnovni program\n");</pre>
	<pre style="margin-top: 0cm; margin-right: 0cm; margin-left: 0cm; margin-bottom: 0.0001pt; font-size: 10pt; font-family: &#39;Courier New&#39;; ">&nbsp;</pre>
	<pre style="margin-top: 0cm; margin-right: 0cm; margin-left: 0cm; margin-bottom: 0.0001pt; font-size: 10pt; font-family: &#39;Courier New&#39;; ">&nbsp;&nbsp; return 0;</pre>
	<pre style="margin-top: 0cm; margin-right: 0cm; margin-left: 0cm; margin-bottom: 0.0001pt; font-size: 10pt; font-family: &#39;Courier New&#39;; ">}</pre>
</span></div>
<p style="font-size: 12pt; font-family: &#39;Times New Roman&#39;; ">Drugi program 
nasumično generira signale (četri odabrana, SIGINT nije u tom skupu) i šalje ih 
u slučajnim vremenskim intervalima (od 3 do 5 sekundi) procesu za obradu prekida 
(PID mu se zadaje preko komandne linije). Kada proces koji šalje signale 
(generator) primi 
(npr. od korisnika preko tipkovnice) signal SIGINT, tada proces treba poslati 
signal SIGKILL procesu koji prihvaća signale te nakon toga i sam završiti s 
radom.</p>
<p style="font-size: 12pt; font-family: &#39;Times New Roman&#39;; ">Kostur rješenja 
programa za slanje signala dan je sljedećim kodom:</p>
<p style="font-size: 12pt; font-family: &#39;Times New Roman&#39;; ">
<font size="2" face="Courier New">#include &lt;stdio.h&gt;<br>
#include &lt;signal.h&gt;<br>
#include &lt;stdlib.h&gt;<br>
<br>
int pid=0;<br>
<br>
void prekidna_rutina(int sig){<br>
&nbsp;&nbsp; /* pošalji SIGKILL procesu 'pid'*/<br>
&nbsp;&nbsp; exit(0);<br>
}<br>
<br>
int main(int argc, char *argv[]){<br>
&nbsp;&nbsp; pid=atoi(argv[1]);<br>
&nbsp;&nbsp; sigset(SIGINT, prekidna_rutina);<br>
<br>
&nbsp;&nbsp; while(1){<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; /* odspavaj 3-5 sekundi */<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; /* slučajno odaberi jedan signal (od 4) */<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; /* pošalji odabrani signal procesu 'pid' funkcijom kill*/<br>
&nbsp;&nbsp; }<br>
&nbsp;&nbsp; return 0;<br>
}</font></p>
<p style="font-size: 12pt; font-family: &#39;Times New Roman&#39;; "><font size="3">
Zgodno je programe pokretati iz dvije ljuske (iz jedne program za obradu 
prekida, a iz druge program za generiranje prekida). Program za generiranje 
signala mora se pokrenuti drugi da bi mogao dobiti identifikacijski broj prvog 
procesa kome šalje signale.</font></p>
<p style="font-size: 12pt; font-family: &#39;Times New Roman&#39;; "><font size="3">
Ispis programa za obradu prekida treba izgledati vrlo slično kao u nastavku:</font></p>
<p style="font-size: 12pt; font-family: &#39;Times New Roman&#39;; ">
<font size="2" face="Courier New">~/os1/vj1&gt; ./obrada<span class="Apple-converted-space">&nbsp;</span><br>
Proces obrade prekida, PID=10962</font><font size="2"><br>
</font><font size="2" face="Courier New">G 1 2 3 4 5<br>
-----------<br>
1 - - - - -<br>
2 - - - - -<br>
3 - - - - -<br>
4 - - - - -<br>
</font><font size="3"><br>
Nakon pokretanja prvog programa i kada se zna PID prvog procesa (u ovom slučaju 10962) u drugoj 
ljusci (dvije ljuske možete dobiti tako da se dvaput logirate) se pokrene drugi 
program koji generira prekide:</font><span class="Apple-converted-space">&nbsp;</span><font face="Courier New"><br>
~/os1/vj1&gt; ./generator_prekida 10962<br>
</font><font size="3"><br>
Tada bi se u prvoj ljusci trebalo ispisivati (stanja 
varijabli nije nužno potrebno ispisivati!):</font></p>
<p style="font-family: &#39;Times New Roman&#39;">
<span class="Apple-style-span" style="border-collapse: separate; color: rgb(0, 0, 0); font-family: Times New Roman; font-style: normal; font-variant: normal; font-weight: normal; letter-spacing: normal; line-height: normal; orphans: 2; text-align: -webkit-auto; text-indent: 0px; text-transform: none; white-space: normal; widows: 2; word-spacing: 0px; -webkit-border-horizontal-spacing: 0px; -webkit-border-vertical-spacing: 0px; -webkit-text-decorations-in-effect: none; -webkit-text-size-adjust: auto; -webkit-text-stroke-width: 0px; ">
<font face="Courier New" size="2">GP S1 S2 S3 S4 S5<br>
-----------------<br>
&nbsp;1&nbsp; -&nbsp; -&nbsp; -&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 0 0 0 0 ]&nbsp; TEK_PRIOR=0&nbsp; PRIOR[0 0 0 0 0 0 ]<br>
&nbsp;2&nbsp; -&nbsp; -&nbsp; -&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 0 0 0 0 ]&nbsp; TEK_PRIOR=0&nbsp; PRIOR[0 0 0 0 0 0 ]<br>
&nbsp;3&nbsp; -&nbsp; -&nbsp; -&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 0 0 0 0 ]&nbsp; TEK_PRIOR=0&nbsp; PRIOR[0 0 0 0 0 0 ]<br>
&nbsp;4&nbsp; -&nbsp; -&nbsp; -&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 0 0 0 0 ]&nbsp; TEK_PRIOR=0&nbsp; PRIOR[0 0 0 0 0 0 ]<br>
&nbsp;5&nbsp; -&nbsp; -&nbsp; -&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 0 0 0 0 ]&nbsp; TEK_PRIOR=0&nbsp; PRIOR[0 0 0 0 0 0 ]<br>
&nbsp;6&nbsp; -&nbsp; -&nbsp; -&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 0 0 0 0 ]&nbsp; TEK_PRIOR=0&nbsp; PRIOR[0 0 0 0 0 0 ]<br>
&nbsp;7&nbsp; -&nbsp; -&nbsp; -&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 0 0 0 0 ]&nbsp; TEK_PRIOR=0&nbsp; PRIOR[0 0 0 0 0 0 ]<br>
&nbsp;8&nbsp; -&nbsp; -&nbsp; -&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 0 0 0 0 ]&nbsp; TEK_PRIOR=0&nbsp; PRIOR[0 0 0 0 0 0 ]<br>
&nbsp;9&nbsp; -&nbsp; -&nbsp; -&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 0 0 0 0 ]&nbsp; TEK_PRIOR=0&nbsp; PRIOR[0 0 0 0 0 0 ]<br>
&nbsp;-&nbsp; X&nbsp; -&nbsp; -&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 0 0 0 0 ]&nbsp; TEK_PRIOR=0&nbsp; PRIOR[0 0 0 0 0 0 ]<br>
&nbsp;-&nbsp; P&nbsp; -&nbsp; -&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 0 0 0 0 ]&nbsp; TEK_PRIOR=1&nbsp; PRIOR[0 0 0 0 0 0 ]<br>
&nbsp;-&nbsp; 1&nbsp; -&nbsp; -&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 0 0 0 0 ]&nbsp; TEK_PRIOR=1&nbsp; PRIOR[0 0 0 0 0 0 ]<br>
&nbsp;-&nbsp; 2&nbsp; -&nbsp; -&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 0 0 0 0 ]&nbsp; TEK_PRIOR=1&nbsp; PRIOR[0 0 0 0 0 0 ]<br>
&nbsp;-&nbsp; 3&nbsp; -&nbsp; -&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 0 0 0 0 ]&nbsp; TEK_PRIOR=1&nbsp; PRIOR[0 0 0 0 0 0 ]<br>
&nbsp;-&nbsp; 4&nbsp; -&nbsp; -&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 0 0 0 0 ]&nbsp; TEK_PRIOR=1&nbsp; PRIOR[0 0 0 0 0 0 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; X&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 0 0 0 0 ]&nbsp; TEK_PRIOR=1&nbsp; PRIOR[0 0 0 0 0 0 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; P&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 0 0 0 0 ]&nbsp; TEK_PRIOR=3&nbsp; PRIOR[0 0 0 1 0 0 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; 1&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 0 0 0 0 ]&nbsp; TEK_PRIOR=3&nbsp; PRIOR[0 0 0 1 0 0 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; 2&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 0 0 0 0 ]&nbsp; TEK_PRIOR=3&nbsp; PRIOR[0 0 0 1 0 0 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; 3&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 0 0 0 0 ]&nbsp; TEK_PRIOR=3&nbsp; PRIOR[0 0 0 1 0 0 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; X&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 0 0 0 0 ]&nbsp; TEK_PRIOR=3&nbsp; PRIOR[0 0 0 1 0 0 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; 4&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 0 1 0 0 ]&nbsp; TEK_PRIOR=3&nbsp; PRIOR[0 0 0 1 0 0 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; 5&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 0 1 0 0 ]&nbsp; TEK_PRIOR=3&nbsp; PRIOR[0 0 0 1 0 0 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; K&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 0 1 0 0 ]&nbsp; TEK_PRIOR=3&nbsp; PRIOR[0 0 0 1 0 0 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; P&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 0 0 0 0 ]&nbsp; TEK_PRIOR=3&nbsp; PRIOR[0 0 0 1 0 0 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; -&nbsp; X&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 0 0 0 0 ]&nbsp; TEK_PRIOR=3&nbsp; PRIOR[0 0 0 1 0 0 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; -&nbsp; P&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 0 0 0 0 ]&nbsp; TEK_PRIOR=4&nbsp; PRIOR[0 0 0 1 3 0 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; -&nbsp; 1&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 0 0 0 0 ]&nbsp; TEK_PRIOR=4&nbsp; PRIOR[0 0 0 1 3 0 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; -&nbsp; 2&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 0 0 0 0 ]&nbsp; TEK_PRIOR=4&nbsp; PRIOR[0 0 0 1 3 0 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; -&nbsp; 3&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 0 0 0 0 ]&nbsp; TEK_PRIOR=4&nbsp; PRIOR[0 0 0 1 3 0 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; -&nbsp; 4&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 0 0 0 0 ]&nbsp; TEK_PRIOR=4&nbsp; PRIOR[0 0 0 1 3 0 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; -&nbsp; X&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 0 0 0 0 ]&nbsp; TEK_PRIOR=4&nbsp; PRIOR[0 0 0 1 3 0 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; -&nbsp; 5&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 0 0 1 0 ]&nbsp; TEK_PRIOR=4&nbsp; PRIOR[0 0 0 1 3 0 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; -&nbsp; K&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 0 0 1 0 ]&nbsp; TEK_PRIOR=4&nbsp; PRIOR[0 0 0 1 3 0 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; -&nbsp; P&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 0 0 0 0 ]&nbsp; TEK_PRIOR=4&nbsp; PRIOR[0 0 0 1 3 0 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; -&nbsp; 1&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 0 0 0 0 ]&nbsp; TEK_PRIOR=4&nbsp; PRIOR[0 0 0 1 3 0 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; -&nbsp; 2&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 0 0 0 0 ]&nbsp; TEK_PRIOR=4&nbsp; PRIOR[0 0 0 1 3 0 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; X&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 0 0 0 0 ]&nbsp; TEK_PRIOR=4&nbsp; PRIOR[0 0 0 1 3 0 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; -&nbsp; 3&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 0 1 0 0 ]&nbsp; TEK_PRIOR=4&nbsp; PRIOR[0 0 0 1 3 0 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; -&nbsp; 4&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 0 1 0 0 ]&nbsp; TEK_PRIOR=4&nbsp; PRIOR[0 0 0 1 3 0 ]<br>
&nbsp;-&nbsp; -&nbsp; X&nbsp; -&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 0 1 0 0 ]&nbsp; TEK_PRIOR=4&nbsp; PRIOR[0 0 0 1 3 0 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; -&nbsp; 5&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 1 1 0 0 ]&nbsp; TEK_PRIOR=4&nbsp; PRIOR[0 0 0 1 3 0 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; -&nbsp; K&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 1 1 0 0 ]&nbsp; TEK_PRIOR=4&nbsp; PRIOR[0 0 0 1 3 0 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; 1&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 1 1 0 0 ]&nbsp; TEK_PRIOR=3&nbsp; PRIOR[0 0 0 1 0 0 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; 2&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 1 1 0 0 ]&nbsp; TEK_PRIOR=3&nbsp; PRIOR[0 0 0 1 0 0 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; 3&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 1 1 0 0 ]&nbsp; TEK_PRIOR=3&nbsp; PRIOR[0 0 0 1 0 0 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; 4&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 1 1 0 0 ]&nbsp; TEK_PRIOR=3&nbsp; PRIOR[0 0 0 1 0 0 ]<br>
^C -&nbsp; -&nbsp; -&nbsp; -&nbsp; -&nbsp; X&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 1 1 0 0 ]&nbsp; TEK_PRIOR=3&nbsp; PRIOR[0 0 0 1 0 0 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; -&nbsp; -&nbsp; P&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 1 1 0 0 ]&nbsp; TEK_PRIOR=5&nbsp; PRIOR[0 0 0 1 0 3 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; X&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 1 1 0 0 ]&nbsp; TEK_PRIOR=5&nbsp; PRIOR[0 0 0 1 0 3 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; -&nbsp; -&nbsp; 1&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 1 2 0 0 ]&nbsp; TEK_PRIOR=5&nbsp; PRIOR[0 0 0 1 0 3 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; -&nbsp; -&nbsp; 2&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 1 2 0 0 ]&nbsp; TEK_PRIOR=5&nbsp; PRIOR[0 0 0 1 0 3 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; -&nbsp; -&nbsp; 3&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 1 2 0 0 ]&nbsp; TEK_PRIOR=5&nbsp; PRIOR[0 0 0 1 0 3 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; -&nbsp; -&nbsp; 4&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 1 2 0 0 ]&nbsp; TEK_PRIOR=5&nbsp; PRIOR[0 0 0 1 0 3 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; X&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 1 2 0 0 ]&nbsp; TEK_PRIOR=5&nbsp; PRIOR[0 0 0 1 0 3 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; -&nbsp; -&nbsp; 5&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 1 3 0 0 ]&nbsp; TEK_PRIOR=5&nbsp; PRIOR[0 0 0 1 0 3 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; -&nbsp; -&nbsp; K&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 1 3 0 0 ]&nbsp; TEK_PRIOR=5&nbsp; PRIOR[0 0 0 1 0 3 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; 5&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 1 3 0 0 ]&nbsp; TEK_PRIOR=3&nbsp; PRIOR[0 0 0 1 0 0 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; K&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 1 3 0 0 ]&nbsp; TEK_PRIOR=3&nbsp; PRIOR[0 0 0 1 0 0 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; P&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 1 2 0 0 ]&nbsp; TEK_PRIOR=3&nbsp; PRIOR[0 0 0 1 0 0 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; 1&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 1 2 0 0 ]&nbsp; TEK_PRIOR=3&nbsp; PRIOR[0 0 0 1 0 0 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; 2&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 1 2 0 0 ]&nbsp; TEK_PRIOR=3&nbsp; PRIOR[0 0 0 1 0 0 ]<br>
&nbsp;-&nbsp; -&nbsp; X&nbsp; -&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 1 2 0 0 ]&nbsp; TEK_PRIOR=3&nbsp; PRIOR[0 0 0 1 0 0 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; 3&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 2 2 0 0 ]&nbsp; TEK_PRIOR=3&nbsp; PRIOR[0 0 0 1 0 0 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; 4&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 2 2 0 0 ]&nbsp; TEK_PRIOR=3&nbsp; PRIOR[0 0 0 1 0 0 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; 5&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 2 2 0 0 ]&nbsp; TEK_PRIOR=3&nbsp; PRIOR[0 0 0 1 0 0 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; K&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 2 2 0 0 ]&nbsp; TEK_PRIOR=3&nbsp; PRIOR[0 0 0 1 0 0 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; P&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 2 1 0 0 ]&nbsp; TEK_PRIOR=3&nbsp; PRIOR[0 0 0 1 0 0 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; 1&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 2 1 0 0 ]&nbsp; TEK_PRIOR=3&nbsp; PRIOR[0 0 0 1 0 0 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; 2&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 2 1 0 0 ]&nbsp; TEK_PRIOR=3&nbsp; PRIOR[0 0 0 1 0 0 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; 3&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 2 1 0 0 ]&nbsp; TEK_PRIOR=3&nbsp; PRIOR[0 0 0 1 0 0 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; 4&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 2 1 0 0 ]&nbsp; TEK_PRIOR=3&nbsp; PRIOR[0 0 0 1 0 0 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; 5&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 2 1 0 0 ]&nbsp; TEK_PRIOR=3&nbsp; PRIOR[0 0 0 1 0 0 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; K&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 2 1 0 0 ]&nbsp; TEK_PRIOR=3&nbsp; PRIOR[0 0 0 1 0 0 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; P&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 2 0 0 0 ]&nbsp; TEK_PRIOR=3&nbsp; PRIOR[0 0 0 1 0 0 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; 1&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 2 0 0 0 ]&nbsp; TEK_PRIOR=3&nbsp; PRIOR[0 0 0 1 0 0 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; 2&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 2 0 0 0 ]&nbsp; TEK_PRIOR=3&nbsp; PRIOR[0 0 0 1 0 0 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; 3&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 2 0 0 0 ]&nbsp; TEK_PRIOR=3&nbsp; PRIOR[0 0 0 1 0 0 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; 4&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 2 0 0 0 ]&nbsp; TEK_PRIOR=3&nbsp; PRIOR[0 0 0 1 0 0 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; 5&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 2 0 0 0 ]&nbsp; TEK_PRIOR=3&nbsp; PRIOR[0 0 0 1 0 0 ]<br>
&nbsp;-&nbsp; -&nbsp; -&nbsp; K&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 2 0 0 0 ]&nbsp; TEK_PRIOR=3&nbsp; PRIOR[0 0 0 1 0 0 ]<br>
&nbsp;-&nbsp; -&nbsp; P&nbsp; -&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 1 0 0 0 ]&nbsp; TEK_PRIOR=2&nbsp; PRIOR[0 0 1 0 0 0 ]<br>
&nbsp;-&nbsp; -&nbsp; 1&nbsp; -&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 1 0 0 0 ]&nbsp; TEK_PRIOR=2&nbsp; PRIOR[0 0 1 0 0 0 ]<br>
&nbsp;-&nbsp; -&nbsp; 2&nbsp; -&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 1 0 0 0 ]&nbsp; TEK_PRIOR=2&nbsp; PRIOR[0 0 1 0 0 0 ]<br>
&nbsp;-&nbsp; -&nbsp; 3&nbsp; -&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 1 0 0 0 ]&nbsp; TEK_PRIOR=2&nbsp; PRIOR[0 0 1 0 0 0 ]<br>
&nbsp;-&nbsp; -&nbsp; 4&nbsp; -&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 1 0 0 0 ]&nbsp; TEK_PRIOR=2&nbsp; PRIOR[0 0 1 0 0 0 ]<br>
&nbsp;-&nbsp; -&nbsp; 5&nbsp; -&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 1 0 0 0 ]&nbsp; TEK_PRIOR=2&nbsp; PRIOR[0 0 1 0 0 0 ]<br>
&nbsp;-&nbsp; -&nbsp; K&nbsp; -&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 1 0 0 0 ]&nbsp; TEK_PRIOR=2&nbsp; PRIOR[0 0 1 0 0 0 ]<br>
&nbsp;-&nbsp; -&nbsp; P&nbsp; -&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 0 0 0 0 ]&nbsp; TEK_PRIOR=2&nbsp; PRIOR[0 0 1 0 0 0 ]<br>
&nbsp;-&nbsp; -&nbsp; 1&nbsp; -&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 0 0 0 0 ]&nbsp; TEK_PRIOR=2&nbsp; PRIOR[0 0 1 0 0 0 ]<br>
&nbsp;-&nbsp; -&nbsp; 2&nbsp; -&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 0 0 0 0 ]&nbsp; TEK_PRIOR=2&nbsp; PRIOR[0 0 1 0 0 0 ]<br>
&nbsp;-&nbsp; -&nbsp; 3&nbsp; -&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 0 0 0 0 ]&nbsp; TEK_PRIOR=2&nbsp; PRIOR[0 0 1 0 0 0 ]<br>
&nbsp;-&nbsp; -&nbsp; 4&nbsp; -&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 0 0 0 0 ]&nbsp; TEK_PRIOR=2&nbsp; PRIOR[0 0 1 0 0 0 ]<br>
&nbsp;-&nbsp; -&nbsp; 5&nbsp; -&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 0 0 0 0 ]&nbsp; TEK_PRIOR=2&nbsp; PRIOR[0 0 1 0 0 0 ]<br>
&nbsp;-&nbsp; -&nbsp; K&nbsp; -&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 0 0 0 0 ]&nbsp; TEK_PRIOR=2&nbsp; PRIOR[0 0 1 0 0 0 ]<br>
&nbsp;-&nbsp; 5&nbsp; -&nbsp; -&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 0 0 0 0 ]&nbsp; TEK_PRIOR=1&nbsp; PRIOR[0 0 0 0 0 0 ]<br>
&nbsp;-&nbsp; K&nbsp; -&nbsp; -&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
O_CEK[0 0 0 0 0 0 ]&nbsp; TEK_PRIOR=1&nbsp; PRIOR[0 0 0 0 0 0 ]<br>
10&nbsp; -&nbsp; -&nbsp; -&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; O_CEK[0 
0 0 0 0 0 ]&nbsp; TEK_PRIOR=0&nbsp; PRIOR[0 0 0 0 0 0 ]<br>
11&nbsp; -&nbsp; -&nbsp; -&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; O_CEK[0 
0 0 0 0 0 ]&nbsp; TEK_PRIOR=0&nbsp; PRIOR[0 0 0 0 0 0 ]<br>
12&nbsp; -&nbsp; -&nbsp; -&nbsp; -&nbsp; -&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; O_CEK[0 
0 0 0 0 0 ]&nbsp; TEK_PRIOR=0&nbsp; PRIOR[0 0 0 0 0 0 ]<br>
Killed</font></span></p>
<p style="font-size: 12pt; font-family: &#39;Times New Roman&#39;; ">X - označava pojavu 
signala, P početak obrade, K završetak obrade, a brojevi koliko je sekundi 
potrošeno na obradu.</p>
<p style="font-size: 12pt; font-family: &#39;Times New Roman&#39;; ">U ispisu se mogu 
uočiti tri stvari. Prvo,<span class="Apple-converted-space">&nbsp;</span><font face="Courier New">^C</font><span class="Apple-converted-space">&nbsp;</span>znači 
da je procesu došao signal SIGINT s tipkovnice, a drugo<span class="Apple-converted-space">&nbsp;</span><font face="Courier New">Killed<span class="Apple-converted-space">&nbsp;</span></font>znači 
da je program za slanje signala završio s radom (i prije toga poslao SIGKILL). I 
treće, u primjeru ispisa program pamti više prekida iste razine 
(OZNAKA_ČEKANJA[i] se ne postavlja u 1 kao što je navedeno u pseudokodu, već se 
povećava za 1).<span class="Apple-converted-space">&nbsp;</span></p>
</span>
