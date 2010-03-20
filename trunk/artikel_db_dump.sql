--
-- PostgreSQL database dump
--

SET statement_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = off;
SET check_function_bodies = false;
SET client_min_messages = warning;
SET escape_string_warning = off;

SET search_path = public, pg_catalog;

SET default_tablespace = '';

SET default_with_oids = false;

--
-- Name: artikel; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE artikel (
    id integer NOT NULL,
    nr character varying(60) NOT NULL,
    beschreibung text,
    hersteller_id integer NOT NULL,
    vk_preis numeric(8,2),
    create_date timestamp without time zone DEFAULT now()
);


ALTER TABLE public.artikel OWNER TO postgres;

--
-- Name: hersteller; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE hersteller (
    id integer NOT NULL,
    name character varying(80) NOT NULL,
    strasse character varying(120),
    plz character varying(10),
    ort character varying(120),
    telefon character varying(40),
    fax character varying(40),
    create_date timestamp without time zone DEFAULT now(),
    email character varying(120)
);


ALTER TABLE public.hersteller OWNER TO postgres;

--
-- Name: lieferant; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE lieferant (
    id integer NOT NULL,
    name character varying(120) NOT NULL,
    strasse character varying(120),
    plz character varying(10),
    ort character varying(120),
    telefon character varying(40),
    fax character varying(40),
    email character varying(120),
    create_date timestamp without time zone DEFAULT now()
);


ALTER TABLE public.lieferant OWNER TO postgres;

--
-- Name: liefert; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE liefert (
    id integer NOT NULL,
    artikel_id integer NOT NULL,
    lieferant_id integer NOT NULL,
    ek_preis numeric(8,2),
    vh_date timestamp without time zone,
    create_date timestamp without time zone DEFAULT now()
);


ALTER TABLE public.liefert OWNER TO postgres;

--
-- Data for Name: artikel; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY artikel (id, nr, beschreibung, hersteller_id, vk_preis, create_date) FROM stdin;
2	175	Testartikel2	3	17.00	2010-03-04 15:13:42.707159
3	0815	testartikel	2	99.99	2010-03-04 15:42:42.576175
4	75a	Mal schauen was passiert =)	2	20.00	2010-03-04 19:54:44.998997
5	123	123	10	123.00	2010-03-04 20:08:21.750582
6	234	234	3	234.00	2010-03-04 20:09:01.880056
7	555	555	3	555.00	2010-03-04 20:18:33.174706
\.


--
-- Data for Name: hersteller; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY hersteller (id, name, strasse, plz, ort, telefon, fax, create_date, email) FROM stdin;
1	Acer	Groheweg 18-24	12345	Musterstadt	9277-37749020	9277-3774911	2010-03-03 22:25:30.291951	info@acer.de
2	Medion	Groheweg 26-28	12345	Musterstadt	9277-377332	9277-377333	2010-03-03 22:26:51.148091	info@medion.de
3	Dell	Groheweg 32-36	12345	Musterstadt	9277-35522	9277-35520	2010-03-03 22:27:26.235507	info@dell.de
10	Express	Groheweg 32-36	12345	Musterstadt	9277-37749020	9277-3774911	2010-03-03 23:17:25.548053	info@express.de
\.


--
-- Data for Name: lieferant; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY lieferant (id, name, strasse, plz, ort, telefon, fax, email, create_date) FROM stdin;
1	Hermes	Groheweg 18-24	12345	Musterstadt	9277-37749020	9277-3774911	info@hermes.de	2010-03-03 22:28:40.452081
2	UPS	Groheweg 26-28	12345	Musterstadt	9277-37749020	9277-3774911	info@ups.de	2010-03-03 22:29:06.099985
3	DHL	Groheweg 32-36	12345	Musterstadt	9277-37749020	9277-3774911	info@dhl.de	2010-03-03 22:29:26.16408
\.


--
-- Data for Name: liefert; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY liefert (id, artikel_id, lieferant_id, ek_preis, vh_date, create_date) FROM stdin;
1	2	2	5.00	2010-03-04 00:00:00	2010-03-04 22:00:44.478211
2	5	3	100.00	2010-03-02 00:00:00	2010-03-04 22:02:18.535804
3	5	1	100.00	2010-03-04 00:00:00	2010-03-04 22:02:34.6469
\.


--
-- Name: artikel_nr_key; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY artikel
    ADD CONSTRAINT artikel_nr_key UNIQUE (nr);


--
-- Name: artikel_pk; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY artikel
    ADD CONSTRAINT artikel_pk PRIMARY KEY (id);


--
-- Name: hersteller_pk; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY hersteller
    ADD CONSTRAINT hersteller_pk PRIMARY KEY (id);


--
-- Name: lieferant_pk; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY lieferant
    ADD CONSTRAINT lieferant_pk PRIMARY KEY (id);


--
-- Name: liefert_pk; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY liefert
    ADD CONSTRAINT liefert_pk PRIMARY KEY (id);


--
-- Name: artikel_fk_hersteller; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY artikel
    ADD CONSTRAINT artikel_fk_hersteller FOREIGN KEY (hersteller_id) REFERENCES hersteller(id);


--
-- Name: liefert_fk_artikel; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY liefert
    ADD CONSTRAINT liefert_fk_artikel FOREIGN KEY (artikel_id) REFERENCES artikel(id);


--
-- Name: liefert_fk_lieferant; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY liefert
    ADD CONSTRAINT liefert_fk_lieferant FOREIGN KEY (lieferant_id) REFERENCES lieferant(id);


--
-- Name: public; Type: ACL; Schema: -; Owner: postgres
--

REVOKE ALL ON SCHEMA public FROM PUBLIC;
REVOKE ALL ON SCHEMA public FROM postgres;
GRANT ALL ON SCHEMA public TO postgres;
GRANT ALL ON SCHEMA public TO PUBLIC;


--
-- PostgreSQL database dump complete
--

